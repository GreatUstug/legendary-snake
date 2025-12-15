#include "Game.h"
#include "../../Include/Constants.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <algorithm>

AppleGenerator::AppleGenerator() : gen(rd()),
xDist(1, COLS_WITH_BORDERS - 2),
yDist(1, ROWS_WITH_BORDERS - 2) {
}

Apple AppleGenerator::Spawn(const Snake& snake) {
    Apple newApple(xDist(gen), yDist(gen));

    const auto& snakeBody = snake.GetBody();
    while (std::any_of(snakeBody.begin(), snakeBody.end(),
        [&](const SnakePart& part) {
            return part.GetX() == newApple.GetX() && part.GetY() == newApple.GetY();
        })) {
        newApple = Apple(xDist(gen), yDist(gen));
    }

    return newApple;
}

char InputHandler::GetInput(char currentDirection) {
    if (_kbhit()) {
        char key = _getch();

        if (key == QUIT) {
            return QUIT;
        }

        if ((key == UP && currentDirection != DOWN) ||
            (key == DOWN && currentDirection != UP) ||
            (key == LEFT && currentDirection != RIGHT) ||
            (key == RIGHT && currentDirection != LEFT)) {
            return key;
        }
    }
    return currentDirection;
}

Game::Game() : score(SNAKE_START_SIZE), gameOver(false), quit(false) {
    Reset();
}

void Game::Reset() {
    snake.Spawn();
    apple = appleGenerator.Spawn(snake);
    gameOver = false;
    quit = false;
    score = SNAKE_START_SIZE;
    lastMoveTime = std::chrono::steady_clock::now();
}

void Game::HandleInput() {
    char input = InputHandler::GetInput(snake.GetDirection());

    if (input == QUIT) {
        quit = true;
        return;
    }

    if (input != snake.GetDirection()) {
        snake.ChangeDirection(input);
    }
}

void Game::Update() {
    if (quit || gameOver) return;

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    if (now - lastMoveTime >= MOVE_INTERVAL) {
        snake.Move();

        if (snake.CheckCollision()) {
            gameOver = true;
            return;
        }

        if (snake.CheckAppleEaten(apple.GetX(), apple.GetY())) {
            apple = appleGenerator.Spawn(snake);
            snake.Grow();
            score++;
        }

        lastMoveTime = now;
    }
}

void Game::Render() {
    grid.Clear();

    grid.SetCell(apple.GetX(), apple.GetY(), APPLE_CHAR);

    // ÈÑÏÐÀÂËÅÍÎ: ïåðåäàåì grid âìåñòî grid.GetGrid()
    snake.DrawOnGrid(grid);

    grid.Print();
}

bool Game::IsGameOver() const {
    return gameOver;
}

bool Game::IsQuit() const {
    return quit;
}

bool Game::IsWon() const {
    return score >= WIN_SCORE;
}

int Game::GetScore() const {
    return score;
}

bool Game::IsSizeGridValid() {
    return SNAKE_START_SIZE <= COLS && SNAKE_START_SIZE <= ROWS;
}

void Game::Run() {
    if (!IsSizeGridValid()) {
        std::cerr << SIZE_EXEP << '\n';
        std::cerr << SIZE_MESS << '\n';
        return;
    }

    while (!IsGameOver() && !IsQuit() && !IsWon()) {
        HandleInput();
        Update();
        Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if (IsQuit()) {
        std::cout << PLAYER_QUIT;
    }
    else if (IsGameOver()) {
        std::cout << LOSE;
    }
    else if (IsWon()) {
        std::cout << WIN;
    }
}
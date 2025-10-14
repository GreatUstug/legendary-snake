#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>

//размерности поля
const int ROWS = 10;
const int COLS = 10;
const int ROWS_WITH_BORDERS = ROWS + 2;
const int COLS_WITH_BORDERS = COLS + 2;
//спец символы
const char BORDER_CHAR = '#';
const char SNAKE_HEAD_CHAR = '@';
const char SNAKE_BODY_CHAR = '+';
const char APPLE_CHAR = '*';
//параметры змейки
const int SNAKE_START_SIZE = 2;
const int SNAKE_HEAD_IND = 0;
//состояния змейки
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';
const char QUIT = 'q';
//время движения
const auto MOVE_INTERVAL = std::chrono::milliseconds(100);

struct SnakePart {
    int x;
    int y;
    char dir;
    char type;
};

struct Apple {
    int x;
    int y;
};

using Grid = std::vector<std::vector<char>>;
using Snake = std::deque<SnakePart>;

//создание поля
Grid CreateGrid()
{
    Grid grid(ROWS_WITH_BORDERS, std::vector<char>(COLS_WITH_BORDERS, ' '));

    fill(grid.front().begin(), grid.front().end(), BORDER_CHAR);
    fill(grid.back().begin(), grid.back().end(), BORDER_CHAR);

    for (auto it = grid.begin() + 1; it != grid.end() - 1; ++it) {
        it->front() = BORDER_CHAR;
        it->back() = BORDER_CHAR;
    }

    return grid;
}


//вывод поля на экран
void PrintGrid(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        std::cout.write(row.data(), row.size());
        std::cout << '\n';
    }
}

//создание змейки
Snake SpawnSnake() {
    const int startX = COLS / 2;
    const int startY = ROWS / 2;

    if (startX + SNAKE_START_SIZE > COLS) {

    }
    
    Snake snake ;

    snake.push_back({ startX, startY, UP, SNAKE_HEAD_CHAR });
    snake.push_back({ startX, startY + 1, UP, SNAKE_BODY_CHAR });

    return snake;
}

//переделать
void DrawSnakeOnGrid(Grid& grid, const Snake& snake) {
    for (size_t i = 0; i < snake.size(); ++i) {
        const auto& part = snake[i];
        if (part.y >= 0 && part.y < static_cast<int>(grid.size()) &&
            part.x >= 0 && part.x < static_cast<int>(grid[SNAKE_HEAD_IND].size())) {
            grid[part.y][part.x] = part.type;
        }
    }
}

//движение змейки
void MoveSnake(Snake& snake) {
    char dir = snake[SNAKE_HEAD_IND].dir;
    SnakePart head = snake.front();

    switch (dir) {
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
        default: return;
    }

    head.type = SNAKE_HEAD_CHAR;
    snake.push_front(head);

    if (snake.size() > 1) {
        snake[1].type = SNAKE_BODY_CHAR;
    }
    snake.pop_back();
}

bool HandleInput(Snake& snake) {
    if (_kbhit()) {
        char key = _getch();
        char currDir = snake[SNAKE_HEAD_IND].dir;

        if (key == QUIT) {
            return true;
        }

        if ((key == UP && currDir != DOWN) ||
            (key == DOWN && currDir != UP) ||
            (key == LEFT && currDir != RIGHT) ||
            (key == RIGHT && currDir != LEFT)) {
            snake[SNAKE_HEAD_IND].dir = key;
        }
        return false;
    }
}


//проверка положения змеи
bool ValidPosition(const SnakePart& snakeHead) {
    if (snakeHead.x <= 0 || snakeHead.x >= COLS_WITH_BORDERS - 1 ||
        snakeHead.y <= 0 || snakeHead.y >= ROWS_WITH_BORDERS - 1
        ) return false;
    return true;
}

//создание яблока
Apple SpawnApple(const Snake& snake) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(1, COLS_WITH_BORDERS - 1);
    std::uniform_int_distribution<> yDist(1, ROWS_WITH_BORDERS - 1);

    Apple newApple;
    newApple.x = xDist(gen);
    newApple.y = yDist(gen);
    while (any_of(snake.begin(), snake.end(), [&](const SnakePart& Part)
        { return Part.x == newApple.x && Part.y == newApple.y; }))
    {
        newApple.x = xDist(gen);
        newApple.y = yDist(gen);
    }
    return newApple;
}

//отрисовка яблока
void DrawAppleOnGrid(Grid& grid, const Apple& apple) {
    grid[apple.y][apple.x] = APPLE_CHAR;
}


void RenderGame() {
    Snake snake = SpawnSnake();
    Apple apple;
    Grid grid;
    auto lastMoveTime = std::chrono::steady_clock::now();

    while (true) {
        if (HandleInput(snake)) return;
        auto now = std::chrono::steady_clock::now();
        if (now - lastMoveTime >= MOVE_INTERVAL) {
            MoveSnake(snake);
            if (!ValidPosition(snake[SNAKE_HEAD_IND])) return;
            lastMoveTime = now;
        }
        system("cls");
        //apple = SpawnApple(snake);
        grid = CreateGrid();
        //DrawAppleOnGrid(grid, apple);
        DrawSnakeOnGrid(grid, snake);
        PrintGrid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() 
{
    std::cout << "PRESS ANY BUTTON TO START PLAY SNAKE!" << '\n';
    std::cin.get();
    system("cls");
    RenderGame();
    return 0;
}
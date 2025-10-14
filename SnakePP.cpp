#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>

//размерности поля
const int rows = 10;
const int cols = 10;
const int rowsWithBorders = rows + 2;
const int colsWithBorders = cols + 2;
//спец символы
const char borderChar = '#';
const char snakeHeadChar = '@';
const char snakeBodyChar = '+';
//параметры змейки
const int snakeStartSize = 2;
const int snakeHeadInd = 0;
//состояния змейки
const char Up = 'w';
const char Left = 'a';
const char Down = 's';
const char Right = 'd';
const char Quit = 'q';
//время движения
const auto moveInterval = std::chrono::milliseconds(100);

struct snakePart {
    int x;
    int y;
    char dir;
    char type;
};

struct apple {
    int x;
    int y;
};

using namespace std;
using Grid = vector<vector<char>>;
using Snake = deque<snakePart>;

//создание поля
Grid createGrid()
{
    Grid grid(rowsWithBorders, vector<char>(colsWithBorders, ' '));

    fill(grid.front().begin(), grid.front().end(), borderChar);
    fill(grid.back().begin(), grid.back().end(), borderChar);

    for (auto it = grid.begin() + 1; it != grid.end() - 1; ++it) {
        it->front() = borderChar;
        it->back() = borderChar;
    }

    return grid;
}


//вывод поля на экран
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        cout.write(row.data(), row.size());
        cout << '\n';
    }
}

//создание змейки
Snake spawnSnake() {
    const int startX = cols / 2;
    const int startY = rows / 2;

    if (startX + snakeStartSize > cols) {

    }
    
    Snake snake ;

    snake.push_back({ startX, startY, Up, snakeHeadChar });
    snake.push_back({ startX, startY + 1, Up, snakeBodyChar });

    return snake;
}

void drawSnakeOnGrid(Grid& grid, const Snake& snake) {
    for (size_t i = 0; i < snake.size(); ++i) {
        const auto& part = snake[i];
        if (part.y >= 0 && part.y < static_cast<int>(grid.size()) &&
            part.x >= 0 && part.x < static_cast<int>(grid[snakeHeadInd].size())) {
            grid[part.y][part.x] = part.type;
        }
    }
}

//движение змейки
void moveSnake(Snake& snake) {
    char dir = snake[snakeHeadInd].dir;
    snakePart head = snake.front();

    switch (dir) {
        case Up: head.y--; break;
        case Down: head.y++; break;
        case Left: head.x--; break;
        case Right: head.x++; break;
        default: return;
    }

    head.type = snakeHeadChar;
    snake.push_front(head);

    if (snake.size() > 1) {
        snake[1].type = snakeBodyChar;
    }
    snake.pop_back();
}

bool handleInput(Snake& snake) {
    if (_kbhit()) {
        char key = _getch();
        char currDir = snake[snakeHeadInd].dir;

        if (key == Quit) {
            return true;
        }

        if ((key == Up && currDir != Down) ||
            (key == Down && currDir != Up) ||
            (key == Left && currDir != Right) ||
            (key == Right && currDir != Left)) {
            snake[snakeHeadInd].dir = key;
        }
        return false;
    }
}

bool validPosition(const snakePart& snakeHead) {
    if (snakeHead.x <= 0 || snakeHead.x >= colsWithBorders - 1 ||
        snakeHead.y <= 0 || snakeHead.y >= rowsWithBorders - 1
        ) return false;
    return true;
}

void renderGame() {
    Snake snake = spawnSnake();
    Grid grid;
    auto lastMoveTime = std::chrono::steady_clock::now();

    while (true) {
        if (handleInput(snake)) return;
        auto now = std::chrono::steady_clock::now();
        if (now - lastMoveTime >= moveInterval) {
            moveSnake(snake);
            if (!validPosition(snake[snakeHeadInd])) return;
            lastMoveTime = now;
        }
        system("cls");
        grid = createGrid();
        drawSnakeOnGrid(grid, snake);
        printGrid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() 
{
    cout << "PRESS ANY BUTTON TO START PLAY SNAKE!" << '\n';
    cin.get();
    system("cls");
    renderGame();
    return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib>
//размерности поля
const int rows = 5;
const int cols = 5;
const int rowsWithBorders = rows + 2;
const int colsWithBorders = cols + 2;
//символы
const char borderChar = '+';
const char snakeHead = '@';
const char snakeBody = '#';
//параметры змейки
const int snakeStartSize = 2;
const int snakeHeadInd = 0;

struct snake {
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

//создание поля
void fillGrid(vector<vector<char>>& grid) {
    grid.clear();
    grid.assign(rowsWithBorders, vector<char>(colsWithBorders, ' '));
    for (int y = 0; y < rowsWithBorders; y++) {
        for (int x = 0; x < colsWithBorders; x++) {
            if (y == 0 || y == rowsWithBorders - 1 || x == 0 || x == colsWithBorders - 1) grid[y][x] = borderChar;
        }
    }
}

//вывод поля на экран
void printGrid(const vector<vector<char>>& grid) {
    for (int y = 0; y < rowsWithBorders; y++) {
        for (int x = 0; x < colsWithBorders; ++x) {
            cout << grid[y][x] << ' ';
        }
        cout << '\n';
    }
}

//создание змейки
void spawnSnake(vector<vector<char>>& grid, vector<snake>& snake) {
    int x = colsWithBorders / 2;
    int y = rowsWithBorders / 2;
    snake[snakeHeadInd] = { x, y++, 'S', snakeHead };
    snake[snakeHeadInd + 1] = { x, y, 'S', snakeBody };
    for (int i = 0; i < snakeStartSize; i++) {
        grid[snake[i].x][snake[i].y] = snake[i].type;
    }
}


//движение змейки
void controlSnake(vector<vector<char>>& grid, vector<snake>& snake) {
    bool gameOver = false;
    char action;
    while (!gameOver) {
        cin >> action;
        int oldX = snake[snakeHeadInd].x;
        int oldY = snake[snakeHeadInd].y;
        switch (action) {
        case 'W':
            snake[snakeHeadInd].x++;
            break;
        case 'A':
            snake[snakeHeadInd].y--;
            break;
        case 'S':
            snake[snakeHeadInd].x--;
            break;
        case 'D':
            snake[snakeHeadInd].y++;
            break;
        default:
            break;
        }
        grid[oldX][oldY] = ' ';
        if (snake[snakeHeadInd].x == 0 || snake[snakeHeadInd].y == 0 || snake[snakeHeadInd].x == colsWithBorders || snake[snakeHeadInd].y == rowsWithBorders) gameOver = true;
        grid[snake[snakeHeadInd].x][snake[snakeHeadInd].y] = snakeHead;
        system("cls");
        printGrid(grid);
    }
}

int main() {
    vector<vector<char>> grid;
    vector<snake> snake{ snakeStartSize };
    cout << "PRESS ANY BUTTON TO START PLAY SNAKE!" << '\n';
    cin.get();
    cout.clear();
    fillGrid(grid);
    spawnSnake(grid, snake);
    printGrid(grid);
    controlSnake(grid, snake);
    return 0;
}
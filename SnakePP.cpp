#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <algorithm>
//размерности поля
const int rows = 5;
const int cols = 5;
const int rowsWithBorders = rows + 2;
const int colsWithBorders = cols + 2;
//символы
const char borderChar = '#';
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
using Grid = vector<vector<char>>;

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


string row2Str(const vector<char>& row) {
    return(string(row.data(), row.size()));
}

vector<string> grid2Strings(const Grid& grid) {
    vector<string> strings;
    strings.reserve(grid.size());
    transform(grid.begin(), grid.end(), back_inserter(strings), row2Str);
    return strings;
}
//вывод поля на экран
void printGrid(const vector<vector<char>>& grid) {
    vector<string> strings = grid2Strings(grid);
    for (const auto& str : strings) {
        cout << str << '\n';
    }
}

//создание змейки
deque<snake> сreateSnake() {
    int x = colsWithBorders / 2;
    int y = rowsWithBorders / 2;
    deque<snake> snakeDeque;
    snakeDeque.push_back({ x, y++, 'S', snakeHead });
    snakeDeque.push_back({ x, y, 'S', snakeBody });
    return snakeDeque;
}


//движение змейки
void controlSnake(vector<vector<char>>& grid, deque<snake>& snake) 
{
    bool gameOver = false;
    char action;
    while (!gameOver) {
        cin.get(action);
        int oldX = snake[snakeHeadInd].x;
        int oldY = snake[snakeHeadInd].y;
        switch (action) {
        case 'w':
        case 'W':
            snake[snakeHeadInd].x++;
            break;
        case 'a':
        case 'A':
            snake[snakeHeadInd].y--;
            break;
        case 's':
        case 'S':
            snake[snakeHeadInd].x--;
            break;
        case 'd':
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

int main() 
{
    cout << "PRESS ANY BUTTON TO START PLAY SNAKE!" << '\n';
    cin.get();
    system("cls");
    vector<vector<char>> grid = createGrid();
    //deque<snake> snake = spawnSnake();
    printGrid(grid);
    //controlSnake(grid, snake);
    return 0;
}
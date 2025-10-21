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
constexpr int ROWS_WITH_BORDERS = ROWS + 2;
constexpr int COLS_WITH_BORDERS = COLS + 2;
//спец символы
const char BORDER_CHAR = '#';
const char SNAKE_HEAD_CHAR = '@';
const char SNAKE_BODY_CHAR = '+';
const char APPLE_CHAR = '*';
const char FIELD_CHAR = ' ';
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
const auto MOVE_INTERVAL = std::chrono::milliseconds(200);
// очистка экрана
const std::string CLEAR_SCREEN = "\033[H";
//счет для выигрыша
constexpr int WIN_SCORE = ROWS * COLS;
//вывод
const std::string INVITE = "PRESS ANY BUTTON TO START PLAY SNAKE! \n";
const std::string SIZE_EXEP = "SNAKE CAN'T BE STARTED. GRID SIZE IS SMALL. IT SHOULD BE " + std::to_string(SNAKE_START_SIZE) + " * " + std::to_string(SNAKE_START_SIZE) + '\n';
const std::string SIZE_MESS = "YOUR SIZE OF GRID " + std::to_string(ROWS) + " * " + std::to_string(COLS) + '\n';
const std::string PLAYER_QUIT = "PLAYER QUIT GAME. \n";
const std::string LOSE = "GAME OVER \n";
const std::string WIN = "YOU WON! SNAKE EAT ALL APPLES! \n";

struct SnakePart 
{
    int x;
    int y;
    char dir;
    char type;
};

struct Apple 
{
    int x;
    int y;
};


struct GameState 
{
    int scoreCounter;
    std::deque<SnakePart> snake;
    Apple apple;
    bool gameOver;
    bool quit;
    std::chrono::steady_clock::time_point lastMoveTime;
};

using Grid = std::vector<std::vector<char>>;

//создание поля
Grid CreateGrid()
{
    Grid grid(ROWS_WITH_BORDERS, std::vector<char>(COLS_WITH_BORDERS, FIELD_CHAR));

    fill(grid.front().begin(), grid.front().end(), BORDER_CHAR);
    fill(grid.back().begin(), grid.back().end(), BORDER_CHAR);

    for (auto it = grid.begin() + 1; it != grid.end() - 1; ++it) 
    {
        it->front() = BORDER_CHAR;
        it->back() = BORDER_CHAR;
    }

    return grid;
}


//вывод поля на экран
void PrintGrid(const std::vector<std::vector<char>>& grid) 
{
    std::cout << CLEAR_SCREEN;
    for (const auto& row : grid) 
    {
        std::cout.write(row.data(), row.size());
        std::cout << '\n';
    }
}

//создание змейки
std::deque<SnakePart> SpawnSnake()
{
    const int startX = COLS / 2;
    const int startY = ROWS / 2;

    std::deque<SnakePart> snake;

    snake.push_back({ startX, startY, UP, SNAKE_HEAD_CHAR });
    snake.push_back({ startX, startY + 1, UP, SNAKE_BODY_CHAR });

    return snake;
}

void DrawSnakeOnGrid(Grid& grid, const std::deque<SnakePart>& snake)
{
    for (size_t i = 0; i < snake.size(); ++i) 
    {
        const auto& part = snake[i];
        grid[part.y][part.x] = part.type;
    }
}

//движение змейки
std::deque<SnakePart> MoveSnake(const std::deque<SnakePart>& snake, const char& direction)
{
    if (snake.empty()) return snake;
    SnakePart head = snake.front();

    switch (direction) 
    {
    case UP: head.y--; break;
    case DOWN: head.y++; break;
    case LEFT: head.x--; break;
    case RIGHT: head.x++; break;
    default: return snake;
    }

    head.type = SNAKE_HEAD_CHAR;
    head.dir = direction;

    std::deque<SnakePart> newSnake;
    newSnake.push_front(head);


    for (size_t i = 1; i < snake.size(); ++i) 
    {
        SnakePart part = snake[i - 1];
        part.type = SNAKE_BODY_CHAR;
        newSnake.push_back(part);
    }

    if (newSnake.size() > snake.size()) newSnake.pop_back();

    return newSnake;
}

char HandleInput(const std::deque<SnakePart>& snake)
{
    if (_kbhit()) 
    {
        char key = _getch();
        char currDir = snake[SNAKE_HEAD_IND].dir;

        if (key == QUIT) 
        {
            return QUIT;
        }

        if ((key == UP && currDir != DOWN) ||
            (key == DOWN && currDir != UP) ||
            (key == LEFT && currDir != RIGHT) ||
            (key == RIGHT && currDir != LEFT)) 
        {
            return key;
        }
    }
}


//проверка положения змеи
bool IsValidPosition(const std::deque<SnakePart>& snake)
{
    SnakePart snakeHead = snake[SNAKE_HEAD_IND];
    std::deque<SnakePart> snakeBody = snake;
    snakeBody.pop_front();

    //проверка на врезание в стену
    if (snakeHead.x <= 0 || snakeHead.x >= COLS_WITH_BORDERS - 1 ||
        snakeHead.y <= 0 || snakeHead.y >= ROWS_WITH_BORDERS - 1
        ) return false;
    //проверка на врезание в саму себя
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].x == snakeHead.x && snake[i].y == snakeHead.y) return false;
    }
    return true;
}

//создание яблока
Apple SpawnApple(const std::deque<SnakePart>& snake)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(1, COLS_WITH_BORDERS - 2);
    std::uniform_int_distribution<> yDist(1, ROWS_WITH_BORDERS - 2);

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

//проверка на поедание яблока
bool IsAppleEaten(const SnakePart& head, const Apple& apple) 
{
    return (head.x == apple.x && head.y == apple.y);
}

//отрисовка яблока
void DrawAppleOnGrid(Grid& grid, const Apple& apple) 
{
    grid[apple.y][apple.x] = APPLE_CHAR;
}

//увеличение змейки
std::deque<SnakePart> IncreaseSnake(const std::deque<SnakePart>& snake)
{
    if (snake.empty()) return snake;
    std::deque<SnakePart> newSnake = snake;
    if (newSnake.size() >= 2) 
    {
        newSnake.push_back(snake.back());
    }
    else 
    {
        newSnake.push_back(snake.back());
        newSnake.back().type = SNAKE_BODY_CHAR;
    }

    return newSnake;
}

GameState StartGame() 
{
    GameState state;
    state.scoreCounter = SNAKE_START_SIZE;
    state.snake = SpawnSnake();
    state.apple = SpawnApple(state.snake);
    state.quit = false;
    state.gameOver = false;
    state.lastMoveTime = std::chrono::steady_clock::now();
    return state;
}

GameState UpdateGameState(const GameState& gameState, const char& inputDir) 
{
    GameState state = gameState;

    if (inputDir == QUIT) {
        state.quit = true;
        return state;
    }

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    
    if (now - state.lastMoveTime >= MOVE_INTERVAL) 
    {
        state.snake = MoveSnake(state.snake, inputDir);
        if (!IsValidPosition(state.snake)) {
            state.gameOver = true;
            return state;
        }
        state.lastMoveTime = now;
    }

    if (IsAppleEaten(state.snake[SNAKE_HEAD_IND], state.apple))
    {
        state.apple = SpawnApple(state.snake);
        state.snake = IncreaseSnake(state.snake);
        state.scoreCounter++;
    }

    return state;
}

bool IsSizeGridValid() {
    return SNAKE_START_SIZE <= COLS && SNAKE_START_SIZE <= ROWS;
}

//создание игры
void RenderGame() 
{
    if (!IsSizeGridValid())
    {
        std::cerr << SIZE_EXEP << '\n';
        std::cerr << SIZE_MESS << '\n';
        return;
    }
    
    GameState state = StartGame();

    while (state.scoreCounter != WIN_SCORE) 
    {
        char inputDir = HandleInput(state.snake);
        state = UpdateGameState(state, inputDir);
        if (state.quit) {
            std::cout << PLAYER_QUIT;
            return;
        }
        if (state.gameOver) {
            std::cout << LOSE;
            return;
        }
        Grid grid = CreateGrid();
        DrawAppleOnGrid(grid, state.apple);
        DrawSnakeOnGrid(grid, state.snake);
        PrintGrid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << WIN;
    return;
}

int main()
{
    std::cout << INVITE;
    std::cin.get();
    system("cls");
    RenderGame();
    return 0;
}
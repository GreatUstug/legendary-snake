#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <chrono>

// Размерности поля
const int ROWS = 10;
const int COLS = 10;
constexpr int ROWS_WITH_BORDERS = ROWS + 2;
constexpr int COLS_WITH_BORDERS = COLS + 2;

// Спец символы
const char BORDER_CHAR = '#';
const char SNAKE_HEAD_CHAR = '@';
const char SNAKE_BODY_CHAR = '+';
const char APPLE_CHAR = '*';
const char FIELD_CHAR = ' ';

// Параметры змейки
const int SNAKE_START_SIZE = 2;

// Направления движения
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';
const char QUIT = 'q';

// Время движения
const auto MOVE_INTERVAL = std::chrono::milliseconds(200);

// Очистка экрана
const std::string CLEAR_SCREEN = "\033[H";

// Счет для выигрыша
constexpr int WIN_SCORE = ROWS * COLS;

// Сообщения
const std::string INVITE = "PRESS ANY BUTTON TO START PLAY SNAKE! \n";
const std::string SIZE_EXEP = "SNAKE CAN'T BE STARTED. GRID SIZE IS SMALL. IT SHOULD BE " +
    std::to_string(SNAKE_START_SIZE) + " * " +
    std::to_string(SNAKE_START_SIZE) + '\n';
const std::string SIZE_MESS = "YOUR SIZE OF GRID " + std::to_string(ROWS) +
    " * " + std::to_string(COLS) + '\n';
const std::string PLAYER_QUIT = "PLAYER QUIT GAME. \n";
const std::string LOSE = "GAME OVER \n";
const std::string WIN = "YOU WON! SNAKE EAT ALL APPLES! \n";

#endif // CONSTANTS_H
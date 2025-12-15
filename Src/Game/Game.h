#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <random>
#include "../Snake/Snake.h"
#include "../Apple/Apple.h"
#include "../Grid/Grid.h"

class AppleGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> xDist;
    std::uniform_int_distribution<> yDist;

public:
    AppleGenerator();
    Apple Spawn(const Snake& snake);
};

class InputHandler {
public:
    static char GetInput(char currentDirection);
};

class Game {
private:
    Snake snake;
    Apple apple;
    AppleGenerator appleGenerator;
    GameGrid grid;
    int score;
    bool gameOver;
    bool quit;
    std::chrono::steady_clock::time_point lastMoveTime;

public:
    Game();
    void Reset();
    void HandleInput();
    void Update();
    void Render();
    void Run();
    bool IsGameOver() const;
    bool IsQuit() const;
    bool IsWon() const;
    int GetScore() const;

private:
    static bool IsSizeGridValid();
};

#endif // GAME_H
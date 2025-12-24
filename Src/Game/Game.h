#ifndef GAME_H
#define GAME_H

#include <chrono>
#include "../Snake/Snake.h"
#include "../Apple/Apple.h"
#include "../Grid/Grid.h"
#include "../AppleGenerator/AppleGenerator.h"
#include "../InputHandler/InputHandler.h"

class Game 
{
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

#endif
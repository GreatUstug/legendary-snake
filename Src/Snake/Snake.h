#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "../SnakePart/SnakePart.h"
#include "../Grid/Grid.h"

class Snake
{
private:
    std::deque<SnakePart> body;
    char currentDirection;
    bool shouldGrow;

public:
    Snake();
    void Spawn();
    void ChangeDirection(char newDir);
    void Move();
    void Grow();
    bool CheckCollision() const;
    bool CheckAppleEaten(int appleX, int appleY) const;
    const std::deque<SnakePart>& GetBody() const;
    size_t GetLength() const;
    char GetDirection() const;
    const SnakePart& GetHead() const;

    void DrawOnGrid(GameGrid& grid) const;
};

#endif
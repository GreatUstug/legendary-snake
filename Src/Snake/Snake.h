#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <vector>

class GameGrid; // Предварительное объявление

class SnakePart {
private:
    int x;
    int y;
    char dir;
    char type;

public:
    SnakePart(int x = 0, int y = 0, char dir = 'w', char type = '+');
    int GetX() const;
    int GetY() const;
    char GetDir() const;
    char GetType() const;
    void SetX(int newX);
    void SetY(int newY);
    void SetDir(char newDir);
    void SetType(char newType);
    bool IsAtPosition(int posX, int posY) const;
};

class Snake {
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

    // Изменено: принимает неконстантную ссылку на GameGrid
    void DrawOnGrid(class GameGrid& grid) const;
};

#endif // SNAKE_H
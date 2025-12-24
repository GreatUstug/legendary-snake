#include "Snake.h"
#include "../../Include/Constants.h"
#include "../SnakePart/SnakePart.h"
#include "../Grid/Grid.h"
#include <algorithm>

Snake::Snake() : currentDirection(UP), shouldGrow(false) 
{
    Spawn();
}

void Snake::Spawn() {
    const int startX = COLS / 2;
    const int startY = ROWS / 2;

    body.clear();
    body.push_back(SnakePart(startX, startY, UP, SNAKE_HEAD_CHAR));
    body.push_back(SnakePart(startX, startY + 1, UP, SNAKE_BODY_CHAR));
    currentDirection = UP;
    shouldGrow = false;
}

void Snake::ChangeDirection(char newDir) {
    if ((newDir == UP && currentDirection != DOWN) ||
        (newDir == DOWN && currentDirection != UP) ||
        (newDir == LEFT && currentDirection != RIGHT) ||
        (newDir == RIGHT && currentDirection != LEFT)) 
    {
        currentDirection = newDir;
    }
}

void Snake::Move() 
{
    if (body.empty()) return;

    SnakePart head = body.front();
    SnakePart newHead = head;

    switch (currentDirection) 
    {
    case UP: newHead.SetY(head.GetY() - 1); break;
    case DOWN: newHead.SetY(head.GetY() + 1); break;
    case LEFT: newHead.SetX(head.GetX() - 1); break;
    case RIGHT: newHead.SetX(head.GetX() + 1); break;
    default: return;
    }

    newHead.SetType(SNAKE_HEAD_CHAR);
    newHead.SetDir(currentDirection);

    body.front().SetType(SNAKE_BODY_CHAR);
    body.push_front(newHead);

    if (!shouldGrow) 
    {
        body.pop_back();
    }
    else 
    {
        shouldGrow = false;
    }
}

void Snake::Grow() 
{
    shouldGrow = true;
}

bool Snake::CheckCollision() const 
{
    if (body.empty()) return true;

    const SnakePart& head = body.front();

    if (head.GetX() <= 0 || head.GetX() >= COLS_WITH_BORDERS - 1 ||
        head.GetY() <= 0 || head.GetY() >= ROWS_WITH_BORDERS - 1) 
    {
        return true;
    }

    for (size_t i = 1; i < body.size(); i++) 
    {
        if (body[i].GetX() == head.GetX() && body[i].GetY() == head.GetY()) 
        {
            return true;
        }
    }

    return false;
}

bool Snake::CheckAppleEaten(int appleX, int appleY) const 
{
    if (body.empty()) return false;
    const SnakePart& head = body.front();
    return (head.GetX() == appleX && head.GetY() == appleY);
}

const std::deque<SnakePart>& Snake::GetBody() const 
{
    return body;
}

size_t Snake::GetLength() const 
{
    return body.size();
}

char Snake::GetDirection() const 
{
    return currentDirection;
}

const SnakePart& Snake::GetHead() const 
{
    return body.front();
}

void Snake::DrawOnGrid(GameGrid& grid) const 
{
    for (const auto& part : body) 
    {
        grid.SetCell(part.GetX(), part.GetY(), part.GetType());
    }
}
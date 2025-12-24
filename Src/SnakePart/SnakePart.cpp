#include "SnakePart.h"

SnakePart::SnakePart(int x, int y, char dir, char type)
    : x(x), y(y), dir(dir), type(type) 
{
}

int SnakePart::GetX() const { return x; }
int SnakePart::GetY() const { return y; }
char SnakePart::GetDir() const { return dir; }
char SnakePart::GetType() const { return type; }

void SnakePart::SetX(int newX) { x = newX; }
void SnakePart::SetY(int newY) { y = newY; }
void SnakePart::SetDir(char newDir) { dir = newDir; }
void SnakePart::SetType(char newType) { type = newType; }

bool SnakePart::IsAtPosition(int posX, int posY) const 
{
    return x == posX && y == posY;
}
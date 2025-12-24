#include "Apple.h"

Apple::Apple(int x, int y) : x(x), y(y) {}

int Apple::GetX() const { return x; }
int Apple::GetY() const { return y; }

void Apple::SetX(int newX) { x = newX; }
void Apple::SetY(int newY) { y = newY; }

bool Apple::IsAtPosition(int posX, int posY) const
{
    return x == posX && y == posY;
}
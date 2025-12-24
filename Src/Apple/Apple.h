#ifndef APPLE_H
#define APPLE_H

class Apple 
{
private:
    int x;
    int y;

public:
    Apple(int x = 0, int y = 0);
    int GetX() const;
    int GetY() const;
    void SetX(int newX);
    void SetY(int newY);
    bool IsAtPosition(int posX, int posY) const;
};

#endif
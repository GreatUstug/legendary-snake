#ifndef SNAKEPART_H
#define SNAKEPART_H

class SnakePart
{
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

#endif
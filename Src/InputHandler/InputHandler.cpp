#include "InputHandler.h"
#include "../../Include/Constants.h"
#include <conio.h>

char InputHandler::GetInput(char currentDirection)
{
    if (_kbhit())
    {
        char key = _getch();

        if (key == QUIT)
        {
            return QUIT;
        }

        if ((key == UP && currentDirection != DOWN) ||
            (key == DOWN && currentDirection != UP) ||
            (key == LEFT && currentDirection != RIGHT) ||
            (key == RIGHT && currentDirection != LEFT))
        {
            return key;
        }
    }
    return currentDirection;
}
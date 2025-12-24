#include "AppleGenerator.h"
#include "../../Include/Constants.h"
#include "../Apple/Apple.h"
#include "../Snake/Snake.h"
#include "../SnakePart/SnakePart.h"
#include <algorithm>

AppleGenerator::AppleGenerator() : gen(rd()),
xDist(1, COLS_WITH_BORDERS - 2),
yDist(1, ROWS_WITH_BORDERS - 2)
{
}

Apple AppleGenerator::Spawn(const Snake& snake)
{
    Apple newApple(xDist(gen), yDist(gen));

    const auto& snakeBody = snake.GetBody();
    while (std::any_of(snakeBody.begin(), snakeBody.end(),
        [&](const SnakePart& part)
        {
            return part.GetX() == newApple.GetX() && part.GetY() == newApple.GetY();
        })) 
    {
        newApple = Apple(xDist(gen), yDist(gen));
    }

    return newApple;
}
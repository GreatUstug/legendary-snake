#ifndef APPLEGENERATOR_H
#define APPLEGENERATOR_H

#include <random>
#include "../Apple/Apple.h"
#include "../Snake/Snake.h"

class AppleGenerator 
{
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> xDist;
    std::uniform_int_distribution<> yDist;

public:
    AppleGenerator();
    Apple Spawn(const Snake& snake);
};

#endif
#include <iostream>
#include "Include/Constants.h"
#include "Src/Game/Game.h"

int main() {
    std::cout << INVITE;
    std::cin.get();
    system("cls");

    Game game;
    game.Run();

    return 0;
}
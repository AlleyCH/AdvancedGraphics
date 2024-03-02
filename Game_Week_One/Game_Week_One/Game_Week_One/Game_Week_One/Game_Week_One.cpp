// Game_Week_One.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Player.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "GameScene.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create and start the game
    GameScene game;
    game.startGame();

    return 0;
}

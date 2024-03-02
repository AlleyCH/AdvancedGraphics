#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread> // Add this include for std::this_thread::sleep_for
#include <chrono> // Add this include for std::chrono::milliseconds
#include "Player.h"

class GameScene {
public:
    GameScene();
    void startGame();

private:
    std::vector<Player> team_a;
    std::vector<Player> team_b;

    bool gameOver() const;
    void updatePlayerPositions();
    void shooting();
    float calculateDistance(const Player::position& pos1, const Player::position& pos2) const;
    Player::position getRandomPosition();
};


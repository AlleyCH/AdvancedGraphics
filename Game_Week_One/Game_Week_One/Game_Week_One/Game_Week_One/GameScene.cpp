#include "GameScene.h"
#include <iostream>
#include <string>

float GameScene::calculateDistance(const Player::position& pos1, const Player::position& pos2) const {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    return sqrt(dx * dx + dy * dy);
}

GameScene::GameScene() {
    // 20 players
    for (int i = 0; i < 20; ++i) {
        Player player_a("Player_A" + std::to_string(i + 1), getRandomPosition());
        Player player_b("Player_B" + std::to_string(i + 1), getRandomPosition());

        player_a.addWeapon(Weapon(30, 20, "AK47"));
        player_b.addWeapon(Weapon(20, 10, "Pistol"));

        team_a.push_back(player_a);
        team_b.push_back(player_b);
    }
}

void GameScene::startGame() {
    while (!gameOver()) {
        updatePlayerPositions();
        shooting();
    }

    if (std::all_of(team_a.begin(), team_a.end(), [](const Player& player) { return player.isDead(); })) {
        std::cout << "GAME IS DONE! \nTeam B wins! \nWeapon used: Pistol" << std::endl;

    }
    else {
        std::cout << "GAME IS DONE! \nTeam A wins! \nWeapon used: AK47" << std::endl;
    }
}

bool GameScene::gameOver() const {
    return std::all_of(team_a.begin(), team_a.end(), [](const Player& player) { return player.isDead(); }) ||
        std::all_of(team_b.begin(), team_b.end(), [](const Player& player) { return player.isDead(); });
}

void GameScene::updatePlayerPositions() {
    for (Player& player : team_a) {
        player.moveTo(getRandomPosition());
    }

    for (Player& player : team_b) {
        player.moveTo(getRandomPosition());
    }
}

void GameScene::shooting() {
    for (Player& shooter : team_a) {
        for (Player& target : team_b){
            float distance = calculateDistance(shooter.pos, target.pos);
            if (distance <= 20) {
                for (Weapon& weapon : shooter.getWeapons()) {
                    int remainingBullets = weapon.shoot();
                    if (remainingBullets > 0) {
                        int damage = weapon.getDamage();
                        
                        if (target.isDead()) {
                            std::cout << shooter.getName() << " killed " << target.getName() << "\n";
                            // Remove dead player from the team
                            team_b.erase(std::remove_if(team_b.begin(), team_b.end(),
                                [](const Player& player) { return player.isDead(); }), team_b.end());
                        } 
                    }
                }
            }
        }
    }

    for (Player& shooter : team_b) {
        for (Player& target : team_a) {
            float distance = calculateDistance(shooter.pos, target.pos);
            if (distance <= 20) {
                for (Weapon& weapon : shooter.getWeapons()) {
                    int remainingBullets = weapon.shoot();
                    if (remainingBullets > 0) {
                        int damage = weapon.getDamage();
                        if (target.isDead()) {
                            std::cout << shooter.getName() << " killed " << target.getName() << "\n";
                            // Remove dead player from the team
                            team_a.erase(std::remove_if(team_a.begin(), team_a.end(),
                                [](const Player& player) { return player.isDead(); }), team_a.end());
                        }
                    }
                }
            }
        }
    }
} 

Player::position GameScene::getRandomPosition() {
    return { static_cast<float>(rand() % 100), static_cast<float>(rand() % 100)};
}
#pragma once
#include <iostream>
#include <vector>
#include "Weapon.h"

class Player
{
private:
	std::string name;
	int health;
	std::vector<Weapon> weapons;

public:
	struct position {
		float x;
		float y;
		
	};

	position pos;

	Player(std::string name, position p);
	std::string getName() const;
	void addWeapon(Weapon w);
	position moveTo(position p);
	std::vector<Weapon> getWeapons();
	std::string printWeapons();
	bool isDead() const;
	void isDamaged(int damage);
};


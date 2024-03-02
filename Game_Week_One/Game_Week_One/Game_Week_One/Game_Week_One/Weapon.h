#pragma once

#include <iostream>

class Weapon
{
private:
	int number_of_bullets;
	int damagePower;
	std::string name;

public:
	std::string getName();
	Weapon(int number_of_bullets, int damagePower, std::string name);
	int shoot();
	int getDamage();
};


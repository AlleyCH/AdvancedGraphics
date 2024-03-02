#include "Player.h"
#include <iostream>
#include <vector>

Player::Player(std::string name, position p)
{
	this->name = name;
	this->health = 100;
	this->pos = p;
	/*
	If you want the player to be spawned at origin:
	this->pos.x = 0.0f; this->pos.y = 0.0f; this->pos.z = 0.0f;
	*/
	Player::weapons = {};
}

std::string Player::getName() const
{
	return name;
}

void Player::addWeapon(Weapon w)
{
	this->weapons.push_back(w);
}

Player::position Player::moveTo(position p)
{
	this->pos = p;
	return this->pos;
}

//Left as Exercise:
//Complete the body of the following functions
std::vector<Weapon> Player::getWeapons()
{
	return weapons;
}

std::string Player::printWeapons()
{
	std::string weaponsList;

	for ( Weapon& weapon : weapons) {
		weaponsList += weapon.getName() + "\n";
	}
	return weaponsList;
}

bool Player::isDead() const
{
	if (health <= 0){
		return true;
	}
}

void Player::isDamaged(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

#include "Weapon.h"

std::string Weapon::getName()
{
	return name;
}

Weapon::Weapon(int number_of_bullets, int damagePower, std::string name)
{
	this->number_of_bullets = number_of_bullets;
	this->damagePower = damagePower;
	this->name = name;
}
int Weapon::shoot()
{
	if (this->number_of_bullets > 0)
	{
		this->number_of_bullets--;
	}
	else
	{
		printf("No more bulets in the rifle!!");
	}
	return this->number_of_bullets;
}
int Weapon::getDamage()
{
	return damagePower;
}
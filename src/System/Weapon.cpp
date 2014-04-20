#include "Weapon.h"

Weapon::Weapon()
{}

HOA::ObjectType Weapon::objectType() const
{
	return HOA::ObjectType::Weapon;
}

int Weapon::maxSpeed() const
{
	//TODO in WeaponBase
	return 1;
}

int Weapon::damage() const
{
	return 5;
	//TODO return base_->damage();
}

int Weapon::reach() const
{
	return 6;
}
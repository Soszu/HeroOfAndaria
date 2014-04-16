#include "System/Attack.h"
#include "System/Creature.h"
#include "System/Weapon.h"

Attack::Attack(HOA::AttackType type, Creature *attacker)
	: type_(type), attacker_(attacker)
{}

HOA::AttackType Attack::type() const
{
	return type_;
}

void Attack::setAttacker(Creature *attacker)
{
	attacker_ = attacker;
}

Creature * Attack::attacker() const
{
	return attacker_;
}

void Attack::setWeapon(Weapon *weapon)
{
	weapon_ = weapon;
}

Weapon * Attack::weapon() const
{
	return weapon_;
}

void Attack::setMissile(Weapon *missile)
{
	missile_ = missile;
}

Weapon * Attack::missile() const
{
	return missile_;
}



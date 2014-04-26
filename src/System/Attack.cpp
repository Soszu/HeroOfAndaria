#include "System/Attack.h"

static int currentUid = 0;

Attack::Attack(HOA::AttackType type, Creature *attacker)
	: uid_(currentUid++), type_(type), attacker_(attacker)
{}

int Attack::uid() const
{
	return uid_;
}

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

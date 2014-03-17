#include "System/Creature.h"

Creature::Creature()
{}

HOA::ObjectType Creature::objectType() const
{
	return HOA::ObjectType::Creature;
}

int Creature::maxSpeed() const
{
	//TODO depending on attributes and skills(?)
	return 10;
}

void Creature::attack(const Attack &attack)
{
}

void Creature::receiveAttack(const Attack &attack)
{
}
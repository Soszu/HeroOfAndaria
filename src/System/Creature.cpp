#include "System/Creature.h"

/**
 * \class Creature
 */

Creature::Creature(const CreatureBase * base) : base(base), hitPoints_(0)
{
	initStats();
}

void Creature::initStats()
{
	if (base != nullptr)
		hitPoints_ = base->fullHitPoints();
}

void Creature::setBase(const CreatureBase* base)
{
	this->base = base;

	if (base == nullptr)
		return;

	initStats();
}

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

UID Creature::uid() const
{
	return base->uid();
}

QString Creature::name() const
{
	return base->name();
}

int Creature::hitPoints() const
{
	return hitPoints_;
}

void Creature::setHitPoints(int hitPoints)
{
	hitPoints_ = hitPoints;
}

int Creature::fullHitPoints() const
{
	return base->fullHitPoints();
}

int Creature::agility() const
{
	return base->agility();
}

int Creature::strength() const
{
	return base->strength();
}

int Creature::intelligence() const
{
	return base->intelligence();
}

int Creature::endurance() const
{
	return base->endurance();
}

/*
const EquipmentCarrier * Creature::equipmentCarrier() const
{
	return equipmentCarrier_;
}
*/

QDataStream & operator << (QDataStream &out, const Creature &creature)
{
	out << creature.base->uid();
	return out;
}

QDataStream & operator >> (QDataStream &in, Creature &creature)
{
	UID uid;
	in >> uid;
	creature.setBase(CreatureModel::creature(uid));

	return in;
}

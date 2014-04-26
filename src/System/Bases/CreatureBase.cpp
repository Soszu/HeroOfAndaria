#include "System/Bases/CreatureBase.h"

CreatureBase::CreatureBase() : CreatureBase(EmptyUid, QString())
{}

CreatureBase::CreatureBase(UID uid, const QString &name) :
	uid_(uid), name_(name), fullHitPoints_(0),
	strength_(0), agility_(0), intelligence_(0), endurance_(0)
{}

CreatureBase::CreatureBase(const CreatureBase &creature) :
	name_(creature.name()), fullHitPoints_(creature.fullHitPoints()),
	strength_(creature.strength()), agility_(creature.agility()),
	intelligence_(creature.intelligence()), endurance_(creature.endurance())
{}

CreatureBase::CreatureBase(const QString &name, int fullHitPoints, int strength,
                           int agility, int intelligence, int endurance) :
	name_(name), fullHitPoints_(fullHitPoints), strength_(strength),
	agility_(agility), intelligence_(intelligence), endurance_(endurance)
{}

UID CreatureBase::uid() const
{
	return uid_;
}

QString CreatureBase::name() const
{
	return name_;
}

void CreatureBase::setName(const QString& name)
{
	name_ = name;
}

int CreatureBase::fullHitPoints() const
{
	return fullHitPoints_;
}

void CreatureBase::setFullHitPoints(int fullHitPoints)
{
	fullHitPoints_ = fullHitPoints;
}

int CreatureBase::strength() const
{
	return strength_;
}

void CreatureBase::setStrength(int strength)
{
	strength_ = strength;
}

int CreatureBase::agility() const
{
	return agility_;
}

void CreatureBase::setAgility(int agility)
{
	agility_ = agility;
}

int CreatureBase::intelligence() const
{
	return intelligence_;
}

void CreatureBase::setIntelligence(int intelligence)
{
	intelligence_ = intelligence;
}

int CreatureBase::endurance() const
{
	return endurance_;
}

void CreatureBase::setEndurance(int endurance)
{
	endurance_ = endurance;
}

QDataStream & operator << (QDataStream &out, const CreatureBase &creature)
{
	out << creature.name() << creature.uid();
	out << creature.fullHitPoints();
	out << creature.strength() << creature.agility() << creature.intelligence() << creature.endurance();


	return out;
}

QDataStream & operator >> (QDataStream &in, CreatureBase &creature)
{
	in >> creature.name_ >> creature.uid_;
	in >> creature.fullHitPoints_;
	in >> creature.strength_ >> creature.agility_ >> creature.intelligence_ >> creature.endurance_;

	return in;
}

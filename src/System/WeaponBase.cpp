#include "WeaponBase.h"

WeaponBase::WeaponBase() : damage_(0),
                           hitRatio_(0),
                           reach_(0),
                           strengthInfluence_(0),
                           agilityInfluence_(0),
                           intelligenceInfluence_(0),
                           weaponType_(HOA::WeaponType::Melee)
{}
/*
WeaponBase::WeaponBase(UID uid, QString name) : uid_(uid),
                                                name_(name),
                                                damage_(0),
                                                hitRatio_(0),
                                                reach_(0),
                                                strengthInfluence_(0),
                                                agilityInfluence_(0),
                                                intelligenceInfluence_(0),
                                                weaponType_(HOA::WeaponType::Melee)
{}*/

WeaponBase::WeaponBase(const WeaponBase& weapon) : damage_(weapon.damage()),
                                                   hitRatio_(weapon.hitRatio()),
                                                   reach_(weapon.reach()),
                                                   strengthInfluence_(weapon.strengthInfluence()),
                                                   agilityInfluence_(weapon.agilityInfluence()),
                                                   intelligenceInfluence_(weapon.intelligenceInfluence()),
                                                   weaponType_(weapon.weaponType())
{}

int WeaponBase::damage() const
{
	return damage_;
}

void WeaponBase::setDamage(int damage)
{
	damage_ = damage;
}

int WeaponBase::hitRatio() const
{
	return hitRatio_;
}

void WeaponBase::setHitRatio(int hitRatio)
{
	hitRatio_ = hitRatio;
}

int WeaponBase::reach() const
{
	return reach_;
}

void WeaponBase::setReach(int reach)
{
	reach_ = reach;
}

int WeaponBase::strengthInfluence() const
{
	return strengthInfluence_;
}

void WeaponBase::setStrengthInfluence(int strengthInfluence)
{
	strengthInfluence_ = strengthInfluence;
}

int WeaponBase::agilityInfluence() const
{
	return agilityInfluence_;
}

void WeaponBase::setAgilityInfluence(int agilityInfluence)
{
	agilityInfluence_ = agilityInfluence;
}

int WeaponBase::intelligenceInfluence() const
{
	return intelligenceInfluence_;
}

void WeaponBase::setIntelligenceInfluence(int intelligenceInfluence)
{
	intelligenceInfluence_ = intelligenceInfluence;
}

WeaponType WeaponBase::weaponType() const
{
	return weaponType_;
}

void WeaponBase::setType(WeaponType type)
{
	weaponType_  = type;
}

QDataStream & operator << (QDataStream &out, const WeaponBase &weapon)
{
	out << weapon.name_ << "(" << weapon.uid_ << ")"
	<< "\nstats:"
	<< "\n\tdamage:                  " << weapon.damage_
	<< "\n\thit ratio:               " << weapon.hitRatio_
	<< "\n\treach:                   " << weapon.reach_
	<< "\n\tstrength influence:      " << weapon.strengthInfluence_
	<< "\n\tagility influence:       " << weapon.agilityInfluence_
	<< "\n\tintelligence influence:  " << weapon.intelligenceInfluence_;
	//TODO wypisać type i ogarnąć wypisywanie na strumienie i debug.
	//<< "\n\ttype:                    " << weapon.endurance_;


	return out;
}

QDataStream & operator >> (QDataStream &in, WeaponBase &weapon)
{
	//TODO;
	return in;
}
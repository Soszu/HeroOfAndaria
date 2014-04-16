#include "WeaponBase.h"

WeaponBase::WeaponBase() : damage_(0),
                           hitRatio_(0),
                           reach_(0),
                           strengthModifier_(0),
                           agilityModifier_(0),
                           intelligenceModifier_(0),
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
                                                   strengthModifier_(weapon.strengthModifier()),
                                                   agilityModifier_(weapon.agilityModifier()),
                                                   intelligenceModifier_(weapon.intelligenceModifier()),
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

int WeaponBase::strengthModifier() const
{
	return strengthModifier_;
}

void WeaponBase::setStrengthModifier(int strengthModifier)
{
	strengthModifier_ = strengthModifier;
}

int WeaponBase::agilityModifier() const
{
	return agilityModifier_;
}

void WeaponBase::setAgilityModifier(int agilityModifier)
{
	agilityModifier_ = agilityModifier;
}

int WeaponBase::intelligenceModifier() const
{
	return intelligenceModifier_;
}

void WeaponBase::setIntelligenceModifier(int intelligenceModifier)
{
	intelligenceModifier_ = intelligenceModifier;
}

HOA::WeaponType WeaponBase::weaponType() const
{
	return weaponType_;
}

void WeaponBase::setType(HOA::WeaponType type)
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
	<< "\n\tstrength influence:      " << weapon.strengthModifier_
	<< "\n\tagility influence:       " << weapon.agilityModifier_
	<< "\n\tintelligence influence:  " << weapon.intelligenceModifier_;
	//TODO wypisać type i ogarnąć wypisywanie na strumienie i debug.
	//<< "\n\ttype:                    " << weapon.endurance_;


	return out;
}

QDataStream & operator >> (QDataStream &in, WeaponBase &weapon)
{
	//TODO;
	return in;
}
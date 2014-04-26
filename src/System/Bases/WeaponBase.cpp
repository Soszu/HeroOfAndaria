#include "WeaponBase.h"

WeaponBase::WeaponBase() : WeaponBase(MinUid)
{}

WeaponBase::WeaponBase(UID uid) : uid_(uid),
                                  weaponType_(HOA::WeaponType::OneHanded),
                                  attackType_(HOA::AttackType::Melee),
                                  damage_(0),
                                  hitRatio_(0),
                                  reach_(0),
                                  strengthModifier_(0),
                                  agilityModifier_(0),
                                  intelligenceModifier_(0)
{}

UID WeaponBase::uid() const
{
	return uid_;
}

HOA::WeaponType WeaponBase::type() const
{
	return weaponType_;
}

void WeaponBase::setType(HOA::WeaponType type)
{
	weaponType_  = type;
}

HOA::AttackType WeaponBase::attackType() const
{
	return attackType_;
}

void WeaponBase::setAttackType(HOA::AttackType type)
{
	attackType_ = type;
}

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

QDataStream & operator << (QDataStream &out, const WeaponBase &weapon)
{
	out << weapon.uid();
	out << QVariant(weapon.type()) << QVariant(weapon.attackType());
	out << weapon.damage() << weapon.hitRatio() << weapon.reach();
	out << weapon.strengthModifier() << weapon.agilityModifier() << weapon.intelligenceModifier();

	return out;
}

QDataStream & operator >> (QDataStream &in, WeaponBase &weapon)
{
	QVariant var;
	in >> weapon.uid_;
	in >> var;
	weapon.weaponType_ = static_cast<HOA::WeaponType>(var.toInt());
	in >> var;
	weapon.attackType_ = static_cast<HOA::AttackType>(var.toInt());
	in >> weapon.damage_ >> weapon.hitRatio_ >> weapon.reach_;
	in >> weapon.strengthModifier_ >> weapon.agilityModifier_ >> weapon.intelligenceModifier_;

	return in;
}

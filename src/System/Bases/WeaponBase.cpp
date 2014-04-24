#include "WeaponBase.h"

WeaponBase::WeaponBase() : WeaponBase(MinUid, QString())
{}

WeaponBase::WeaponBase(UID uid, QString name) : uid_(uid),
                                                name_(name),
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

QString WeaponBase::name() const
{
	return name_;
}

void WeaponBase::setName(const QString& name)
{
	name_ = name;
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
	out << weapon.uid() << weapon.name();
	//out << weapon.type() << weapon.attackType();
	out << weapon.damage() << weapon.hitRatio() << weapon.reach();
	out << weapon.strengthModifier() << weapon.agilityModifier() << weapon.intelligenceModifier();

	return out;
}

QDataStream & operator >> (QDataStream &in, WeaponBase &weapon)
{
	in >> weapon.uid_ >> weapon.name_;
	//in >> weapon.weaponType_ >> weapon.attackType_;
	in >> weapon.damage_ >> weapon.hitRatio_ >> weapon.reach_;
	in >> weapon.strengthModifier_ >> weapon.agilityModifier_ >> weapon.intelligenceModifier_;

	return in;
}

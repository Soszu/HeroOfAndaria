#include "Weapon.h"

Weapon::Weapon(const WeaponBase* base) : base_(base)
{}

HOA::ObjectType Weapon::objectType() const
{
	return HOA::ObjectType::Weapon;
}

void Weapon::setBase(const WeaponBase* base)
{
	base_ = base;
}

UID Weapon::uid() const
{
	return base_->uid();
}

QString Weapon::name() const
{
	return base_->name();
}

HOA::WeaponType Weapon::type() const
{
	return base_->type();
}

HOA::AttackType Weapon::attackType() const
{
	return base_->attackType();
}

int Weapon::maxSpeed() const
{
	//TODO fix maxSpeed/hitRatio conflict
	return 1;
}

int Weapon::damage() const
{
	//TODO
	return 5;
// 	return base_->damage();
}

int Weapon::reach() const
{
	//TODO
	return 6;
// 	return base_->reach();
}

int Weapon::hitRatio() const
{
	return base_->hitRatio();
}

int Weapon::strengthModifier() const
{
	return base_->strengthModifier();
}

int Weapon::agilityModifier() const
{
	return base_->agilityModifier();
}

int Weapon::intelligenceModifier() const
{
	return base_->intelligenceModifier();
}

QDataStream& operator<<(QDataStream& out, const Weapon& weapon)
{
	out << weapon.uid();
	return out;
}

QDataStream& operator>>(QDataStream& in, Weapon& weapon)
{
	UID uid;
	in >> uid;
	weapon.setBase(WeaponModel::weapon(uid));
	return in;
}

#include "Weapon.h"

Weapon::Weapon(const WeaponBase* weaponBase, const ItemBase* itemBase) : Item(itemBase), base_(weaponBase)
{}

Weapon::Weapon(const QString& name) : Weapon(WeaponModel::weapon(name), ItemModel::item(name))
{}

Weapon::Weapon(UID uid): Weapon(WeaponModel::weapon(uid), ItemModel::item(uid))
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

HOA::WeaponType Weapon::type() const
{
	return base_->type();
}

HOA::AttackType Weapon::attackType() const
{
	return base_->attackType();
}

qreal Weapon::maxSpeed() const
{
	//TODO fix maxSpeed/hitRatio conflict
	return 1.0;
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

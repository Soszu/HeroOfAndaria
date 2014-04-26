#ifndef WEAPON_H
#define WEAPON_H

#include "System/Item.h"
#include "System/Bases/WeaponBase.h"

class WeaponBase;

class Weapon : public Item
{
public:
	Weapon(const WeaponBase *weaponBase = nullptr, const ItemBase *itemBase = nullptr);
	Weapon(const QString &name);
	Weapon(UID uid);

	virtual HOA::ObjectType objectType() const;

	void setBase(const WeaponBase *base);

	UID uid() const;

	HOA::WeaponType type() const;
	HOA::AttackType attackType() const;

	int damage() const;
	int reach() const;
	int hitRatio() const;
	int maxSpeed() const;

	int strengthModifier() const;
	int agilityModifier() const;
	int intelligenceModifier() const;

	friend QDataStream & operator << (QDataStream &out, const Weapon &weapon);
	friend QDataStream & operator >> (QDataStream &in, Weapon &weapon);

private:
	const WeaponBase *base_;
};

#endif // WEAPON_H

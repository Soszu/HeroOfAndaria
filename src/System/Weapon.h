#ifndef WEAPON_H
#define WEAPON_H

#include "System/Item.h"
#include "System/WeaponBase.h"

class Weapon : public Item
{
public:
	Weapon();

	virtual HOA::ObjectType objectType() const;

	int maxSpeed() const;

	int damage() const;
	int reach() const;

private:
	WeaponBase *base_;
};

#endif // WEAPON_H

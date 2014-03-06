#ifndef WEAPON_H
#define WEAPON_H

#include "System/Item.h"
#include "System/WeaponBase.h"

class Weapon : public Item
{
public:
	Weapon();

private:
	WeaponBase *base_;
};

#endif // WEAPON_H

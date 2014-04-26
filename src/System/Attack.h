#ifndef ATTACK_H
#define ATTACK_H

#include <QtWidgets>
#include "System/Weapon.h"
#include "System/CommonStrings.h"

class Creature;

class Attack
{
public:
	Attack(HOA::AttackType type = HOA::AttackType::Melee, Creature *attacker = nullptr);

	int uid() const;

	HOA::AttackType type() const;

	void setAttacker(Creature *attacker);
	Creature * attacker() const;

	void setWeapon(Weapon *weapon);
	Weapon * weapon() const;

	void setMissile(Weapon *missile);
	Weapon * missile() const;

private:
	int uid_;

	HOA::AttackType type_;
	Creature *attacker_;

	/** Optional */
	Weapon *weapon_;
	Weapon *missile_;
	//TODO spell


	//TODO more info about the attack
};

class AttackManager
{
public:
	virtual void attack(const Attack &att) = 0;
};

#endif // ATTACK_H

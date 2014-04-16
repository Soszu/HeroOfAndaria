#ifndef ATTACK_H
#define ATTACK_H

namespace HOA {
	enum class AttackType {
		Melee,
		Distance,
		Magic,
	};
}

class Creature;
class Weapon;

class Attack
{
public:
	Attack(HOA::AttackType type, Creature *attacker = nullptr);

	HOA::AttackType type() const;

	void setAttacker(Creature *attacker);
	Creature * attacker() const;

	void setWeapon(Weapon *weapon);
	Weapon * weapon() const;

	void setMissile(Weapon *missile);
	Weapon * missile() const;

private:
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

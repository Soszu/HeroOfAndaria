#ifndef ATTACK_H
#define ATTACK_H

#include "Movable.h"

namespace HOA {
	enum class AttackType {
		Melee,
		Distance,
		Magic,
	};
}

class Creature;

class Attack : public Movable
{
public:
	Attack();

	HOA::AttackType type() const;
	const Creature * attacker() const;

private:
	HOA::AttackType type_;
	const Creature *attacker_;
};

#endif // ATTACK_H

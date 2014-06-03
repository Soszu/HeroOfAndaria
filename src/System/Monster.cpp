#include "System/Monster.h"
#include "AI/AI.h"

Monster::Monster()
{}

HOA::ObjectType Monster::objectType() const
{
	return HOA::ObjectType::Monster;
}

void Monster::advance()
{
	if (hitPoints() > 0) {
		AI *ai = AIFactory::ai(this);
		QVector <AI::Behaviour> behaviours = ai->act();
		for (AI::Behaviour b : behaviours) {
			if (b.behaviour == HOA::AIBehaviour::Walk || b.behaviour == HOA::AIBehaviour::Run)
				move(HOA::Direction::Front);
			if (b.behaviour == HOA::AIBehaviour::Rotate)
				rotate({(qreal)b.first, (qreal)b.second});
			if (b.behaviour == HOA::AIBehaviour::PrimaryAttack) {
				attack(Attack(HOA::AttackType::Melee));
				stop();
			}
		}
	}
	Creature::advance();
}

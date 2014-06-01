#include "Barbarian.h"
#include "AI/AI.h"

Barbarian::Barbarian()
{}

HOA::ObjectType Barbarian::objectType() const
{
	return HOA::ObjectType::Barbarian;
}

void Barbarian::advance()
{
	if (hitPoints() > 0) {
		AI *ai = AIFactory::ai(this);
		QVector<AI::Behaviour> behaviours = ai->act();;
		stop();
		for (AI::Behaviour b : behaviours) {
			if (b.behaviour == HOA::AIBehaviour::Walk || b.behaviour == HOA::AIBehaviour::Run) {
				if (!freezed_)
					move(HOA::Direction::Front);
			}
			if (b.behaviour == HOA::AIBehaviour::Rotate) {
				if (!freezed_)
					setRotation({b.first, b.second}); //TODO check if won't collide after rotating
			}
			if (b.behaviour == HOA::AIBehaviour::PrimaryAttack) {
				if (!freezed_)
					attack(Attack(HOA::AttackType::Melee));

			}
		}
	}
	Creature::advance();
}

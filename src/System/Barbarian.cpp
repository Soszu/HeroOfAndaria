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
					rotate({(qreal)b.first, (qreal)b.second});
			}
			if (b.behaviour == HOA::AIBehaviour::PrimaryAttack) {
				if (!freezed_)
					attack(Attack(HOA::AttackType::Melee));

			}
		}

		//TODO get all checks "freezed_" out of here
	}
	Creature::advance();
}

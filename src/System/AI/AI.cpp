#include "System/AI/AI.h"
#include "System/Utils/Math.h"

/**
 * \class AI
 */

VisibilityManager * AI::visibilityManager_;

AI::AI(Creature *creature) :
	creature_(creature)
{}

void AI::setVisibilityManager(VisibilityManager *visibilityManager)
{
	visibilityManager_ = visibilityManager;
}

/**
 * \class AIFactory
 */

QHash <Creature *, AI *> AIFactory::map_;

AI * AIFactory::ai(Creature *creature)
{
	if (!map_.contains(creature)) {
		map_[creature] = new FollowerAI(creature);  //TODO jak creature umiera trzeba to zwolnic
	}
	return map_[creature];
}

/**
 * \class FollowerAI
 */

FollowerAI::FollowerAI(Creature *creature) :
	AI(creature)
{
}

void FollowerAI::detectPlayer()
{
	//TODO load ray from creature base
	QVector <Object *> objects = visibilityManager_->objectsInCircle(creature_->position(), 500);

	seesPlayer = false;
	for (Object *object : objects)  {
		if (object->objectType() == HOA::ObjectType::Human) {
			if (((Creature *)object)->hitPoints() > 0) {
				seesPlayer = true;
				playerPos = object->position();
			}
		}
	}
}

QVector<AI::Behaviour> FollowerAI::act()
{
	QVector <Behaviour> answer;
	detectPlayer();
	if (seesPlayer) {
		answer.append({HOA::AIBehaviour::Rotate, (int)playerPos.x(), (int)playerPos.y()});
		if (HOA::vectorLength(creature_->position() - playerPos) > 50) {
			answer.append({HOA::AIBehaviour::Walk});
		}
		if (HOA::vectorLength(creature_->position() - playerPos) < 100) {
			answer.append({HOA::AIBehaviour::PrimaryAttack});
		}
	}
	return answer;
}

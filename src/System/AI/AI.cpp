#include "System/AI/AI.h"

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

//TODO AI * ai(Creature *creature) {} // perhaps const Creature *


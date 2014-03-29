#ifndef HUMAN_H
#define HUMAN_H

#include "System/Character.h"
#include "System/QuestCarrier.h"

class Human : public QuestCarrier, public Character
{
public:
	Human();

	virtual HOA::ObjectType objectType() const;
};

#endif // HUMAN_H

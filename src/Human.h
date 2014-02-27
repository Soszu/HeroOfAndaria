#ifndef HUMAN_H
#define HUMAN_H

#include "Character.h"
#include "QuestCarrier.h"

class Human : public QuestCarrier, public Character
{
public:
	Human();
};

#endif // HUMAN_H

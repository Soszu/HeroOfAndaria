#ifndef INN_H
#define INN_H

#include "System/Place.h"
#include "System/QuestCarrier.h"

class Inn : public QuestCarrier, public Place
{
public:
	Inn(const QString &name);
	virtual HOA::PlaceType type() const;
};

#endif // INN_H

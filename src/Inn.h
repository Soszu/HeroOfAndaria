#ifndef INN_H
#define INN_H

#include "Place.h"
#include "QuestCarrier.h"

class Inn : public QuestCarrier, public Place
{
public:
	Inn(const QString &name);
};

#endif // INN_H

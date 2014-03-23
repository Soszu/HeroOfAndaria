#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include "System/EquipmentCarrier.h"
#include "System/Place.h"

class Blacksmith : public Place, public EquipmentCarrier
{
public:
	Blacksmith(const QString &name);
	virtual HOA::PlaceType type() const;
	
};

#endif // BLACKSMITH_H

#ifndef TOWN_H
#define TOWN_H

#include <QtCore>
#include "System/Object.h"
#include "System/Place.h"

class Town : public Object
{
public:
	Town();

	virtual HOA::ObjectType objectType() const;

	const QVector <Place *> & places() const;
	void visitPlace(Place *p);
	void addPlace(Place * p);
private:
	QVector <Place *> places_;
};

#endif // TOWN_H

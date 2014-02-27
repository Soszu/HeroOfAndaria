#ifndef TOWN_H
#define TOWN_H

#include <QtCore>
#include "Object.h"
#include "Place.h"

class Town : public Object
{
public:
	Town();

	const QVector <Place *> & places() const;

private:
	QVector <Place *> places_;
};

#endif // TOWN_H

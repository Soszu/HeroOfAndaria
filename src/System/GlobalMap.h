#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include <QtCore>
#include "System/Map.h"
#include "System/Town.h"
#include "System/LocalMap.h"

class GlobalMap : public Map
{
Q_OBJECT;

public:
	GlobalMap(int width, int height, Human *player);

	virtual bool canCollide(const Movable *lhs, const Object *rhs) const;
	virtual void onCollision(Object *object, const QVector <Object *> &collisions);

	virtual void addObject(Object *object);

	QVector <Town *> towns() const;
	Town * currentTown() const;

	void enterTown(Town *town);
	void exitTown(Town *town);

	QVector <Location *> locations() const;
	Location * currentLocation() const;

	void enterLocation(Location *location);
	void exitLocation(Location *location);

signals:
	void townEntered();
	void townExited();

	void locationEntered();
	void locationExited();

private:
	Town *currentTown_;
	Location *currentLocation_;

	void test();

private slots:
	void onTownExited();
	void onLocationExited();
};

#endif // GLOBAL_MAP_H

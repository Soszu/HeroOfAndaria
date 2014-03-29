#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include <QtCore>
#include "System/Map.h"
#include "System/Town.h"

class GlobalMap : public Map
{
Q_OBJECT;

public:
	GlobalMap(int width, int height);

	virtual bool canCollide(const Movable *lhs, const Object *rhs) const;
	virtual void onCollision(Object *object, const QVector <Object *> &collisions);

	QVector <Town *> towns() const;
	Town * currentTown() const;

	void enterTown(Town *town);
	void exitTown(Town *town);

signals:
	void townEntered();
	void townExited();

private:
	Town *currentTown_;

	virtual void addObject(Object *object);

private slots:
	void onTownExited();
};

#endif // GLOBAL_MAP_H

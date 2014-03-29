#ifndef MAP_H
#define MAP_H

#include <QtWidgets>
#include "System/Object.h"
#include "System/Human.h"
#include "System/Grid.h"

class Map : public Grid
{
Q_OBJECT;

public:
	Map(int width, int height);

	Object * newestObject();
	const QVector <Object *> & objects() const;

	Human * player();

	virtual bool canCollide(const Movable *lhs, const Object *rhs) const;
	virtual void onCollision(Object *object, const QVector <Object *> &collisions);

protected:
	QVector <Object *> objects_;
	Object *newestObject_;
	Human *player_;

	virtual void addObject(Object *object);

signals:
	void objectAdded();
};

#endif // MAP_H

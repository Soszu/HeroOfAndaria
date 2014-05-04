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
	Map(int width, int height, Human *player);

	Object * newestObject();
	const QVector <Object *> & objects() const;

	Human * player();

	virtual bool canCollide(const Movable *lhs, const Object *rhs) const;
	virtual void onCollision(Object *object, const QVector <Object *> &collisions);

	virtual void addObject(Object *object);

	void activate();
	void deactivate();

signals:
	void objectAdded();

protected:
	QVector <Object *> objects_;
	Object *newestObject_;
	Human *player_;

	QTimer *advanceTimer_;

private:
	void test();
};

#endif // MAP_H

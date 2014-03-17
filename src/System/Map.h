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

protected:
	QVector <Object *> objects_;
	Human *player_;

	void addObject(Object *object);

signals:
	void objectAdded();
};

#endif // MAP_H

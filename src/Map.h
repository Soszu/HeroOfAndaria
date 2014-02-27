#ifndef MAP_H
#define MAP_H

#include <QtWidgets>
#include "Object.h"
#include "Grid.h"

class Map : public Grid
{
public:
	Map(int width, int height);

protected:
	QVector <Object *> objects_;
};

#endif // MAP_H

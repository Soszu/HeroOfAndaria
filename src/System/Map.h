#ifndef MAP_H
#define MAP_H

#include <QtWidgets>
#include "System/Object.h"
#include "System/Grid.h"

class Map : public Grid
{
public:
	Map(int width, int height);

protected:
	QVector <Object *> objects_;
};

#endif // MAP_H

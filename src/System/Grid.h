#ifndef GRID_H
#define GRID_H

#include <QtCore>
#include "System/Tile.h"

class Grid
{
public:
	Grid(int width, int height);

	int width() const;
	int height() const;

protected:
	QVector <Tile *> tiles_;

private:
	int width_;
	int height_;
};

#endif // GRID_H
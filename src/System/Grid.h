#ifndef GRID_H
#define GRID_H

#include <QtCore>
#include "System/Tile.h"

class Grid : public QObject
{
public:
	Grid(int width, int height);

	int width() const;
	int height() const;

	const QVector <Tile> & tiles() const;
	const Tile & tile(int index) const;
	void addTile(const Tile &tile);
	void changeTile(const Tile &tile, int index);

protected:
	QVector <Tile> tiles_;

private:
	int width_;
	int height_;
};

#endif // GRID_H

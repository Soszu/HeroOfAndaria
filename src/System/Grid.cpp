#include "System/Grid.h"

Grid::Grid(int width, int height)
	: width_(width), height_(height)
{
	tiles_.resize(width * height);
	for (int w = 0; w < width; ++w)
		for (int h = 0; h < height; ++h)
			tiles_[w + h * width] = Tile();
}

int Grid::tileSize()
{
	static const int TILE_SIZE = 10;
	return TILE_SIZE;
}

int Grid::width() const
{
	return width_;
}

int Grid::height() const
{
	return height_;
}

const QVector <Tile> & Grid::tiles() const
{
	return tiles_;
}

const Tile & Grid::tile(int index) const
{
	Q_ASSERT(qBound(0, index, tiles_.size() - 1));
	return tiles_[index];
}

void Grid::addTile(const Tile &tile)
{
	tiles_.append(tile);
}

void Grid::changeTile(const Tile &tile, int index)
{
	Q_ASSERT(qBound(0, index, tiles_.size() - 1));
	tiles_[index] = tile;
}
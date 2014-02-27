#ifndef TILE_H
#define TILE_H

namespace HOA {
	enum class Terrain {
		Grass,
		Sand,
		Rock,
	};
}

class Tile
{
public:
	Tile(HOA::Terrain terrain, int height);

	HOA::Terrain terrain() const;
	int height() const;

private:
	HOA::Terrain terrain_;
	int height_;
};

#endif // TILE_H

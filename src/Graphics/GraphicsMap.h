#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "System/Map.h"

/**
 * \class TileScene
 * Scene with tiny tiles.
 */

class TileScene : public QGraphicsScene
{
Q_OBJECT;
public:
	TileScene(Map *map);
	~TileScene();

private:
	Map *map_;

	static const int TILE_SIZE           = 2;
	static const int BIG_TILE_MULTIPLIER = 15;
	static const int BIG_TILE_SIZE       = TILE_SIZE * BIG_TILE_MULTIPLIER;

	QVector <const QPixmap *> tiles_;
	QVector <QPair <QPixmap, int> > bigTiles_;

	void initBackground();

	const QPixmap * newTile(const Tile &tile) const;
	QRectF rectForTile(int x, int y) const;
	void addTile(const QPixmap *pixmap);
	void setTile(int x, int y, const QPixmap *pixmap);

	void drawBackground(QPainter *painter, const QRectF &exposed);
};

/**
 * \class GraphicsMap
 * Graphical representation of a Map.
 */

namespace HOA {
	/** Numbers are important */
	enum class MapAction : quint8 {
		Up    = 0,
		Left  = 1,
		None  = 2,
		Down  = 3,
		Right = 4,
	};
}

class GraphicsMap : public QGraphicsView
{
Q_OBJECT;

public:
	GraphicsMap(Map *map);

	void updateCursor(const QPoint &position);

protected:
	Map *map_;

	void addGraphicsObject(GraphicsObject *object);

	struct {
		HOA::MapAction horizontalDirection;
		HOA::MapAction verticalDirection;
	} mapActions_;

	static QHash <int, HOA::MapAction> keyToMapAction_;

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

protected slots:
	void onObjectAdded();

private:
	TileScene tileScene_;

	QPoint cursorPosition_;

	void initWindow();
	void initGraphicsObjects();
	void initScene();
	void initMapActions();
	void initMap();

	HOA::Direction mapActionDirection() const;
};

#endif // GRAPHICSMAP_H

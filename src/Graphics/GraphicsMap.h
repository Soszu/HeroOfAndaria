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

	static int bigTileMultiplier();
	static int bigTileSize();

	QVector <QPair <QPixmap, int> > bigTiles_;

	void initBackground();

	const QPixmap * newTile(const Tile &tile) const;
	QRectF rectForTile(int x, int y) const;
	void addTile(const Tile &tile);

	void drawBackground(QPainter *painter, const QRectF &exposed);
};

namespace HOA {
	/** Numbers are important */
	enum class MapAction : quint8 {
		Up    = 0,
		Left  = 1,
		None  = 2,
		Down  = 3,
		Right = 4,

		Menu  = 5,
	};
}

/**
 * \class GraphicsMap
 * Graphical representation of a Map.
 */
class GraphicsMap : public QGraphicsView
{
Q_OBJECT;

public:
	GraphicsMap(Map *map);

	void updateCursor();

signals:
	void menuActivated();

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

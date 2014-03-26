#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "Graphics/KeyboardManager.h"
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

/**
 * \class GraphicsMap
 * Graphical representation of a Map.
 */
class GraphicsMap : public QGraphicsView, public MovementManager
{
Q_OBJECT;

public:
	GraphicsMap(Map *map);

	void updateCursor();

	virtual bool canMakeMove(const Movable *object, const QPoint &vector) const;

signals:
	void menuActivated();

protected:
	Map *map_;

	void addGraphicsObject(GraphicsObject *graphicsObject);

	struct {
		HOA::KeyFunction horizontalDirection;
		HOA::KeyFunction verticalDirection;
	} mapActions_;

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

private slots:
	void onCollision();
};

#endif // GRAPHICSMAP_H

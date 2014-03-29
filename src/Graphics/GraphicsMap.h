#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "Graphics/KeyboardManager.h"
#include "System/Map.h"

class MapView;
class TileScene;

/**
 * \class GraphicsMap
 * Graphical representation of a Map.
 */
class GraphicsMap : public QStackedWidget, public MovementManager
{
Q_OBJECT;

public:
	GraphicsMap(Map *map);
	~GraphicsMap();

	virtual bool canMakeMove(const Movable *object, const QPoint &vector) const;

signals:
	void menuActivated();

protected:
	Map *map_;

	MapView *mapView_;

	struct {
		HOA::KeyFunction horizontalDirection;
		HOA::KeyFunction verticalDirection;
	} mapActions_;

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

protected slots:
	void onCollision();

private:
	void initMap();
	void initMapActions();
	void initView();
	void initLayout();

	HOA::Direction mapActionDirection() const;

private slots:
	void onObjectAdded();
};

/**
 * \class MapView
 */

class MapView : public QGraphicsView
{
Q_OBJECT;

public:
	MapView(Map *map);
	~MapView();

signals:
	void collided();

private:
	Map *map_;
	TileScene *tileScene_;

	void initMap();
	void initWindow();
	void initGraphicsObjects();
	void initScene();
	void initCursor();
	void initView();

	void addGraphicsObject(GraphicsObject *graphicsObject);

private slots:
	void updateCursor();

	void onObjectAdded();
};

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

	QPixmap newTile(const Tile &tile) const;
	QRectF rectForTile(int x, int y) const;
	void addTile(const Tile &tile);

	void drawBackground(QPainter *painter, const QRectF &exposed);
};

#endif // GRAPHICSMAP_H

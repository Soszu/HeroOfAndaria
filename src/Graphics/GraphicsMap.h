#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "Graphics/KeyboardManager.h"
#include "System/AI/AI.h"
#include "System/Map.h"
#include "Panels.h"

class MapView;
class TileScene;

/**
 * \class GraphicsMap
 * Graphical representation of a Map.
 */
class GraphicsMap : public QStackedWidget, public MovementManager, public AttackManager, public VisibilityManager
{
Q_OBJECT;

public:
	GraphicsMap(Map *map);
	~GraphicsMap();

	virtual bool canMove(const Movable *object, const QPointF &vector, qreal angle = 0.0) const;
	virtual bool canRotate(const Movable *object, qreal angle) const;
	virtual int collisionType(const Object *lhs, const Object *rhs) const;
	virtual void collide(Object *lhs, Object *rhs);

	virtual void attack(const Attack &attack);

	virtual QVector <Object *> objectsInCircle(const QPointF &center, qreal ray);

	static HOA::Direction keysToDirection(HOA::KeyFunction horizontal, HOA::KeyFunction vertical);

	void reinit();

signals:
	void menuActivated();

protected:
	Map *map_;

	MapView *mapView_;

	struct {
		HOA::KeyFunction horizontalDirection;
		HOA::KeyFunction verticalDirection;
	} mapActions_;

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

protected slots:
	void onCollision(QObject *object);

private:
	void initMap();
	void initManagement();
	void initView();
	void initLayout();
	void initObject(Object *object);

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

	void reinit();

	void setCameraHorizontalAction(HOA::KeyFunction action);
	void setCameraVerticalAction(HOA::KeyFunction action);

	int scrollSpeed();

	void zoom(int delta);

signals:
	void collided(QObject *object);

private:
	Map *map_;
	TileScene *tileScene_;

	QTimer scrollTimer_;
	HOA::Direction scrollDirection_;

	struct {
		HOA::KeyFunction horizontalDirection;
		HOA::KeyFunction verticalDirection;
	} cameraActions_;

	void initMap();
	void initWindow();
	void initGraphicsObjects();
	void initScene();
	void initCursor();
	void initView();
	void initPanels();

	void addGraphicsObject(GraphicsObject *graphicsObject);

	void checkScrolling();
	void scroll(const QPoint &change);
	QPoint scrollPosition() const;

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private slots:
	void updateCursor();
	void onScroll();

	void onObjectAdded();
	void onCollision();

	void onPlayerMoved();
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

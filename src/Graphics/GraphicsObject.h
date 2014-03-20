#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QtWidgets>
#include "System/Object.h"

//TODO along with functions from Movable take all math-like ones and put into one file

class GraphicsObject : public QGraphicsObject
{
Q_OBJECT;

public:
	GraphicsObject(Object *object);
	virtual ~GraphicsObject();

	Object * object();

	QVector <GraphicsObject *> collisions(const QPoint &vector = QPoint(0, 0));

	static qreal vectorAngle(const QPoint &middle, const QPoint &vector);

signals:
	void collided();

protected:
	Object *object_;

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected slots:
	virtual void advance();

private:
	QVector <GraphicsObject *> collisions_;

	void checkCollisions();

private slots:
	void adjustPosition();
	void adjustRotation();
};

#endif // GRAPHICSOBJECT_H

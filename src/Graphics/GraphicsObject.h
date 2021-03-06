#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QtWidgets>
#include "System/Object.h"

namespace HOA {
	namespace ZValue {
		enum Value {
			Background = 0,
			Ground     = 1,
			LowLevel   = 2,
			HighLevel  = 3,
			Building   = 4,
			Tree       = 5,
			Clouds     = 6,
		};
	}
}

class GraphicsObject : public QGraphicsObject
{
Q_OBJECT;

public:
	GraphicsObject(Object *object);
	virtual ~GraphicsObject();

	Object * object();

	virtual QPainterPath figureShape() const;
	virtual QPainterPath shape() const;

	QVector <GraphicsObject *> collisions(const QPointF &vector = QPointF(0.0, 0.0), qreal angle = 0.0);

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

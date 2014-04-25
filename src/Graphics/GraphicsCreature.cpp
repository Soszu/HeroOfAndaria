#include "Graphics/GraphicsCreature.h"
#include "System/DataManager.h"

GraphicsCreature::GraphicsCreature(Creature *creature) :
	GraphicsObject((Object *)creature)
{
	initPixmap();
}

QPolygonF GraphicsCreature::weaponShape() const
{
	return QPolygonF();
}

QPainterPath GraphicsCreature::figureShape() const
{
	QPainterPath figure;
	figure.addEllipse(pointZero().x() - 3.0,
			  pointZero().y() - 3.0,
	                  scale() * pixmap_->width()  + 6.0,
	                  scale() * pixmap_->height() + 6.0);
	return figure;
}

QPainterPath GraphicsCreature::shape() const
{
	QPainterPath path;

	path.addPath(figureShape());
	path.addPolygon(weaponShape());

	return path;
}

int GraphicsCreature::creatureSize() const
{
	static const int CREATURE_SIZE = 60;
	return CREATURE_SIZE;
}

static bool healthVisibilityEnabled_ = false;

void GraphicsCreature::triggerHealthVisibility()
{
	healthVisibilityEnabled_ = !healthVisibilityEnabled_;
}

bool GraphicsCreature::healthVisibilityEnabled()
{
	return healthVisibilityEnabled_;
}

static bool boundingBoxesVisibilityEnabled_ = false;

void GraphicsCreature::triggerBoundingBoxesVisibility()
{
	boundingBoxesVisibilityEnabled_ = !boundingBoxesVisibilityEnabled_;
}

bool GraphicsCreature::boundingBoxesVisibilityEnabled()
{
	return boundingBoxesVisibilityEnabled_;
}

void GraphicsCreature::initPixmap()
{
	pixmap_     = DataManager::pixmap(Data::ImagePath::Wolf);
	pixmapDead_ = DataManager::pixmap(Data::ImagePath::WolfDead);
}

qreal GraphicsCreature::scale() const
{
	return qreal(creatureSize()) / qreal(pixmap_->width());;
}

QPointF GraphicsCreature::pointZero() const
{
	return {qreal(-creatureSize() / 2), qreal(-creatureSize() / 2)};
}

QPointF GraphicsCreature::weaponAttachPoint() const
{
	return {scale() * 4.0, scale() * 18.0};
}

void GraphicsCreature::paintFigure(QPainter *painter)
{
	if (((Creature *)object_)->hitPoints() > 0)
		painter->drawPixmap(pointZero().toPoint(),
		                    pixmap_->scaled(creatureSize(),
		                                    creatureSize(),
		                                    Qt::KeepAspectRatio));
	else
		painter->drawPixmap(pointZero().toPoint(),
		                    pixmapDead_->scaled(creatureSize(),
		                                        creatureSize(),
		                                        Qt::KeepAspectRatio));
}

void GraphicsCreature::paintWeapon(QPainter *painter)
{
	return;
}

void GraphicsCreature::paintBoundingBoxes(QPainter *painter)
{
	painter->save();
	painter->setPen(Qt::red);
	painter->drawPath(shape());
	painter->restore();
}

void GraphicsCreature::paintHealth(QPainter *painter)
{
	static const int LIFE_SIZE = 40;

	painter->save();

	painter->rotate(-rotation());
	qreal lifePercent = qreal(((Creature *)object())->hitPoints())
	                  / qreal(((Creature *)object())->fullHitPoints());

	QPen pen;
	pen.setWidth(3);

	if (lifePercent > 0.0) {
		pen.setColor(Qt::red);
		painter->setPen(pen);
		painter->drawLine(pointZero().toPoint() + QPoint(0, -LIFE_SIZE / 2),
		                  pointZero().toPoint() + QPoint(LIFE_SIZE * lifePercent, -LIFE_SIZE / 2));
	}

	if (lifePercent < 1.0) {
		pen.setColor(Qt::black);
		painter->setPen(pen);
		painter->drawLine(pointZero().toPoint() + QPoint(LIFE_SIZE * lifePercent, -LIFE_SIZE / 2),
		                  pointZero().toPoint() + QPoint(LIFE_SIZE, -LIFE_SIZE / 2));
	}

	painter->restore();
}

QRectF GraphicsCreature::boundingRect() const
{
	return QRectF(-creatureSize(),
	              -creatureSize(),
	              creatureSize() * 2,
	              creatureSize() * 2);
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (GraphicsCreature::healthVisibilityEnabled())
		paintHealth(painter);
	if (GraphicsCreature::boundingBoxesVisibilityEnabled())
		paintBoundingBoxes(painter);
	paintFigure(painter);
	paintWeapon(painter);
}

void GraphicsCreature::advance()
{
	GraphicsObject::advance();
}
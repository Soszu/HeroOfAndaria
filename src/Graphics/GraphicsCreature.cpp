#include "Graphics/GraphicsCreature.h"
#include "System/DataManager.h"

GraphicsCreature::GraphicsCreature(Creature *creature) :
	GraphicsObject((Object *)creature)
{
	initRenderer();
}

QPainterPath GraphicsCreature::weaponShape() const
{
	return QPainterPath();
}

QPainterPath GraphicsCreature::figureShape() const
{
	QPainterPath figure;
	figure.addEllipse(pointZero().x()  - 3.0, pointZero().y()  - 3.0,
	                  creatureWidth()  + 6.0, creatureHeight() + 6.0);
	return figure;
}

QPainterPath GraphicsCreature::shape() const
{
	QPainterPath path;

	path.addPath(figureShape());
	path.addPath(weaponShape());

	return path;
}

int GraphicsCreature::creatureHeight() const
{
	static const int CREATURE_HEIGHT = 60;
	return CREATURE_HEIGHT;
}

int GraphicsCreature::creatureWidth() const
{
	static const int CREATURE_WIDTH = 60;
	return CREATURE_WIDTH;
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

void GraphicsCreature::initRenderer()
{
	renderer_     = DataManager::renderer(Data::ImagePath::Wolf);
	rendererDead_ = DataManager::renderer(Data::ImagePath::WolfDead);
}

qreal GraphicsCreature::heightScale() const
{
	return qreal(creatureHeight()) / qreal(renderer_->viewBoxF().height());
}

qreal GraphicsCreature::widthScale() const
{
	return qreal(creatureWidth()) / qreal(renderer_->viewBoxF().width());
}

QPointF GraphicsCreature::pointZero() const
{
	return {qreal(-creatureWidth() / 2), qreal(-creatureHeight() / 2)};
}

QPointF GraphicsCreature::weaponAttachPoint() const
{
	return {widthScale() * 8.0, heightScale() * 22.0};
}

void GraphicsCreature::paintFigure(QPainter *painter)
{
	if (((Creature *)object_)->hitPoints() > 0)
		renderer_->render(painter, QRectF(pointZero().x(), pointZero().y(), creatureWidth(), creatureHeight()));
	else
		rendererDead_->render(painter, QRectF(pointZero().x(), pointZero().y(), creatureWidth(), creatureHeight()));
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
	return QRectF(-creatureWidth()  * 5 / 2,
	              -creatureHeight() * 5 / 2,
	               creatureWidth()  * 5,
	               creatureHeight() * 5);
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (GraphicsCreature::healthVisibilityEnabled())
		paintHealth(painter);
	if (GraphicsCreature::boundingBoxesVisibilityEnabled())
		paintBoundingBoxes(painter);
	if (((Creature *)object())->hitPoints() > 0)
		paintWeapon(painter);
	paintFigure(painter);
}

void GraphicsCreature::advance()
{
	GraphicsObject::advance();
}

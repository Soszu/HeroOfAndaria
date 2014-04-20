#include "Graphics/GraphicsCreature.h"
#include "System/DataManager.h"

GraphicsCreature::GraphicsCreature(Creature *creature)
	: GraphicsObject((Object *)creature)
{
	pixmap_       = DataManager::pixmap(Data::ImagePath::Player);
	weaponPixmap_ = DataManager::pixmap(Data::ImagePath::Sword);

	weaponVector_ = {0.0, 0.0};
	weaponAngle_  = 0.0;
}

int CREATURE_SIZE = 40;

QPolygonF GraphicsCreature::weaponShape() const
{
	QPolygonF weapon;

	QPointF left   = QPointF(scale() * -20.0, scale() * +15.0);
	QPointF right  = QPointF(scale() * +20.0, scale() * +15.0);
	QPointF bottom = QPointF(scale() * +0.0,  scale() * +85.0);

	weapon << left << right << bottom << left;

	QTransform weaponRotationMatrix;
	weaponRotationMatrix.translate(weaponAttachPoint().x() + pointZero().x(),
	                               weaponAttachPoint().y() + pointZero().y());
	weaponRotationMatrix.rotate(weaponAngle_);

	return weaponRotationMatrix.map(weapon);
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

qreal GraphicsCreature::scale() const
{
	return qreal(CREATURE_SIZE) / qreal(pixmap_->width());;
}

QPointF GraphicsCreature::pointZero() const
{
	return {qreal(-CREATURE_SIZE / 2), qreal(-CREATURE_SIZE / 2)};
}

QPointF GraphicsCreature::weaponAttachPoint() const
{
	return {scale() * 4.0, scale() * 18.0};
}

QRectF GraphicsCreature::boundingRect() const
{
	return QRectF(-200.0, -200.0, 400.0, 400.0);
	return shape().boundingRect();
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (((Creature *)object_)->hitPoints() == 0) {
		;//TODO
	} else {
		/** Bounding boxes */

		//painter->setPen(Qt::red);
		//painter->drawPath(shape());

		/** Life */ //TODO visible while 'H' held

		painter->save();

		painter->rotate(-rotation());
		qreal lifePercent = qreal(((Creature *)object())->hitPoints())
		                    / qreal(((Creature *)object())->fullHitPoints());

		QPen pen;
		pen.setWidth(3);

		if (lifePercent > 0) {
			pen.setColor(Qt::red);
			painter->setPen(pen);
			painter->drawLine(pointZero().toPoint() + QPoint(0, -20),
					pointZero().toPoint() + QPoint(40 * lifePercent, -20));
		}

		if (lifePercent < 1) {
			pen.setColor(Qt::black);
			painter->setPen(pen);
			painter->drawLine(pointZero().toPoint() + QPoint(40 * lifePercent, -20),
			                  pointZero().toPoint() + QPoint(40, -20));
		}

		painter->restore();

		/** Figure and weapon */

		painter->drawPixmap(pointZero().toPoint(),
		                    pixmap_->scaled(CREATURE_SIZE, CREATURE_SIZE, Qt::KeepAspectRatio));

		painter->save();
		painter->translate(weaponAttachPoint() + pointZero());
		painter->rotate(weaponAngle_);
		painter->drawPixmap(QPointF(scale() * -18.0, scale() * -5.0),
		                    weaponPixmap_->scaled(qreal(weaponPixmap_->width())  * scale(),
		                                          qreal(weaponPixmap_->height()) * scale()));
		painter->restore();
	}
}

void GraphicsCreature::advance()
{
	//TODO EKHEM. This... "stabbing"... can actually be done better. :)
	//TODO attack, recoil
	if (((Creature *)object_)->currentAction() == HOA::CreatureAction::Attack) {
		// y - degrees, x - timedelta from 0 to 1
		// y = 60x3 - 160x2 + 100x
		qreal x = qreal(((Creature *)object_)->currentActionTime())
		          / qreal(((Creature *)object_)->currentActionTotalTime());
		weaponAngle_ = ((60. * x - 160.) * x + 100.) * x * 5 - 15;
	} else {
		weaponAngle_ = -15;
	}
	GraphicsObject::advance();
}
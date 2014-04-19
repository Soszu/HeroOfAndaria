#include "Graphics/GraphicsCreature.h"
#include "System/DataManager.h"

GraphicsCreature::GraphicsCreature(Creature *creature)
	: GraphicsObject((Object *)creature)
{
	pixmap_       = DataManager::pixmap(Data::ImagePath::Player);
	weaponPixmap_ = DataManager::pixmap(Data::ImagePath::Sword);
}

int CREATURE_SIZE = 40;

QRectF GraphicsCreature::boundingRect() const
{
	return shape().boundingRect();
}

QPainterPath GraphicsCreature::shape() const
{
	// Values specific for the player image with the sword
	int border = 3;
	QPainterPath path;
	path.addEllipse(-CREATURE_SIZE / 2 - border,
	                -CREATURE_SIZE / 2 - border,
	                qreal(CREATURE_SIZE + border * 2),
	                qreal(CREATURE_SIZE) / qreal(pixmap_->width()) * pixmap_->height() + border * 2);
	path.addRect(QRect(-CREATURE_SIZE * 11 / 20 - border,
	                   CREATURE_SIZE * 3 / 10 - border,
	                   CREATURE_SIZE * 3 / 7 + border * 2,
	                   CREATURE_SIZE + border * 2));
	return path;
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (((Creature *)object_)->hitPoints() == 0) {
		;//TODO
	} else {
		/** bounding boxes
		painter->setPen(Qt::red);
		painter->drawPath(shape());
		*/

		qreal scale = qreal(CREATURE_SIZE) / qreal(pixmap_->width());
		painter->drawPixmap(QPoint(-CREATURE_SIZE / 2, -CREATURE_SIZE / 2),
		                    pixmap_->scaled(CREATURE_SIZE, CREATURE_SIZE, Qt::KeepAspectRatio));

		painter->save();
		painter->translate(QPoint(-CREATURE_SIZE * 6 / 10, -CREATURE_SIZE * 2 / 10));
		painter->rotate(weaponAngle);
		painter->drawPixmap(QPoint(0, 0),
		                    weaponPixmap_->scaled(qreal(weaponPixmap_->width())  * scale,
		                                          qreal(weaponPixmap_->height()) * scale));
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
		weaponAngle = ((60. * x - 160.) * x + 100.) * x - 20;
	} else {
		weaponAngle = -20;
	}
	GraphicsObject::advance();
}
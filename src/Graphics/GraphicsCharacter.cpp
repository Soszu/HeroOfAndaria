#include "Graphics/GraphicsCharacter.h"
#include "System/DataManager.h"

GraphicsCharacter::GraphicsCharacter(Character *character) :
	GraphicsCreature(character)
{
	initPixmap();
	weaponVector_ = {0.0, 0.0};
	weaponAngle_  = 0.0;
}

QPolygonF GraphicsCharacter::weaponShape() const
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

QPainterPath GraphicsCharacter::figureShape() const
{
	QPainterPath figure;
	figure.addEllipse(pointZero().x() - 3.0,
	                  pointZero().y() - 3.0,
	                  scale() * pixmap_->width()  + 6.0,
	                  scale() * pixmap_->height() + 6.0);
	return figure;
}

int GraphicsCharacter::creatureSize() const
{
	static const int CHARACTER_SIZE = 40;
	return CHARACTER_SIZE;
}

void GraphicsCharacter::initPixmap()
{
	pixmap_       = DataManager::pixmap(Data::ImagePath::Player);
	pixmapDead_   = DataManager::pixmap(Data::ImagePath::PlayerDead);
	weaponPixmap_ = DataManager::pixmap(Data::ImagePath::Sword);
}

void GraphicsCharacter::paintWeapon(QPainter* painter)
{
	painter->save();
	painter->translate(weaponAttachPoint() + pointZero());
	painter->rotate(weaponAngle_);
	painter->drawPixmap(QPointF(scale() * -18.0, scale() * -5.0),
	                    weaponPixmap_->scaled(qreal(weaponPixmap_->width())  * scale(),
	                                          qreal(weaponPixmap_->height()) * scale()));
	painter->restore();
}

void GraphicsCharacter::advance()
{
	//TODO EKHEM. This... "stabbing"... can actually be done better. :)
	//TODO attack, recoil
	if (((Creature *)object_)->currentAction() == HOA::CreatureAction::Attack) {
		// y - degrees, x - timedelta from 0 to 1
		// y = 60x3 - 160x2 + 100x
		qreal x = qreal(((Creature *)object_)->currentActionTime())
		          / qreal(((Creature *)object_)->currentActionTotalTime());
		weaponAngle_ = ((60.0 * x - 160.0) * x + 100.0) * x * 5 - 15;
	} else {
		weaponAngle_ = -15;
	}
	GraphicsCreature::advance();
}


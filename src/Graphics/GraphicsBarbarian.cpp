#include "GraphicsBarbarian.h"
#include "System/DataManager.h"

GraphicsBarbarian::GraphicsBarbarian(Barbarian *barbarian) :
	GraphicsCreature(barbarian)
{
	initRenderer();
	weaponVector_ = {0.0, 0.0};
	weaponAngle_  = 0.0;
}

QPainterPath GraphicsBarbarian::weaponShape() const
{
	QPainterPath weapon;
	QPolygonF weaponMainFrame;

	QPointF left   = QPointF(widthScale() * -20.0, heightScale() * +15.0);
	QPointF right  = QPointF(widthScale() * +20.0, heightScale() * +15.0);
	QPointF bottom = QPointF(widthScale() * +0.0,  heightScale() * +85.0);

	weaponMainFrame << left << right << bottom << left;
	weapon.addPolygon(weaponMainFrame);

	QTransform weaponRotationMatrix;
	weaponRotationMatrix.translate(weaponAttachPoint().x() + pointZero().x(),
	                               weaponAttachPoint().y() + pointZero().y());
	weaponRotationMatrix.rotate(weaponAngle_);

	return weaponRotationMatrix.map(weapon);
}

int GraphicsBarbarian::creatureHeight() const
{
	static const int CHARACTER_HEIGHT = 36;
	return CHARACTER_HEIGHT;
}

int GraphicsBarbarian::creatureWidth() const
{
	static const int CHARACTER_WIDTH = 70;
	return CHARACTER_WIDTH;
}

void GraphicsBarbarian::initRenderer()
{
	renderer_     = DataManager::renderer(Data::ImagePath::Barbarian);
	rendererDead_ = DataManager::renderer(Data::ImagePath::BarbarianDead);
	weaponRender_ = DataManager::renderer(Data::ImagePath::Axe);
}

void GraphicsBarbarian::paintWeapon(QPainter *painter)
{
	if (((Creature *)object_)->hitPoints() > 0) {
		painter->save();

		painter->translate(weaponAttachPoint() + pointZero());
		painter->rotate(weaponAngle_);
		weaponRender_->render(painter, QRectF(widthScale() * -18.0, heightScale() * -5.0,
		                                      weaponRender_->viewBoxF().width() * widthScale(),
		                                      weaponRender_->viewBoxF().height() * heightScale()));
		painter->restore();
	}
}

void GraphicsBarbarian::advance()
{
	//TODO EKHEM. This... "stabbing"... can actually be done better. :)
	//TODO attack, recoil
	if (((Creature *)object_)->currentAction() == HOA::CreatureAction::Attack) {
		// y - degrees, x - timedelta from 0 to 1
		// y = 60x3 - 160x2 + 100x
		qreal x = qreal(creature()->effect(HOA::PerformingAction).duration) / 500.0; //TODO this should be dependent on what is in Creature, no? ;)
		weaponAngle_ = ((60.0 * x - 160.0) * x + 100.0) * x * 5.0 - 15.0;
	} else {
		weaponAngle_ = -15.0;
	}
	GraphicsCreature::advance();
}


#include "Graphics/GraphicsCreature.h"
#include "System/DataManager.h"

GraphicsCreature::GraphicsCreature(Creature *creature)
	: GraphicsObject((Object *)creature)
{
	pixmap_ = DataManager::pixmap(Data::ImagePath::Player);
}

int CREATURE_SIZE = 40;

QRectF GraphicsCreature::boundingRect() const
{
	return pixmap_->scaled(CREATURE_SIZE, CREATURE_SIZE, Qt::KeepAspectRatio).rect().translated(-CREATURE_SIZE / 2, -CREATURE_SIZE / 2);
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (((Creature *)object_)->hitPoints() == 0)
		;//TODO
	else
		painter->drawPixmap(QPoint(-CREATURE_SIZE / 2, -CREATURE_SIZE / 2),
		                    pixmap_->scaled(CREATURE_SIZE, CREATURE_SIZE, Qt::KeepAspectRatio));
}

void GraphicsCreature::advance()
{
	//TODO attack, recoil
	GraphicsObject::advance();
}
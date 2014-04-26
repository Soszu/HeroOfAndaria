#include "Graphics/GraphicsItem.h"
#include "System/Paths.h"
#include "System/DataManager.h"
GraphicsItem::GraphicsItem(Item *item)
	: GraphicsObject((Object *)item)
{
	this->item_ = item;
}

QString GraphicsItem::getImgPathNormal()
{
	return Data::path(Data::ImagePath::ItemNormal);
}

QString GraphicsItem::getImgPathDark()
{
	return Data::path(Data::ImagePath::ItemDark);
}

Item * GraphicsItem::item()
{
	return this->item_;
}

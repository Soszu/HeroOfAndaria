#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include "Graphics/GraphicsObject.h"
#include "System/Item.h"
#include <QtWidgets>
class GraphicsItem : public GraphicsObject
{
public:
	GraphicsItem(Item *item);
	QString getImgPathNormal();
	QString getImgPathDark();
	Item *item();
private:
	Item *item_;
};

#endif // GRAPHICSITEM_H

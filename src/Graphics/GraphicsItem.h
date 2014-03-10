#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include "Graphics/GraphicsObject.h"
#include "System/Item.h"

class GraphicsItem : public GraphicsObject
{
public:
	GraphicsItem(Item *item);
};

#endif // GRAPHICSITEM_H

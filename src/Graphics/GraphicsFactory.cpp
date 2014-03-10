#include "GraphicsFactory.h"

GraphicsObject * GraphicsFactory::get(Object *object)
{
	GraphicsObject *graphicsObject;
	const Object *constObject = (const Object *)object;
	if (!map_.contains(constObject)) {
		graphicsObject = new GraphicsObject(object);
		map_[constObject] = graphicsObject;
	} else {
		graphicsObject = map_[constObject];
	}
	return graphicsObject;
}

GraphicsObject * GraphicsFactory::get(const Object *object)
{
	Q_ASSERT(map_.contains(object));
	return map_[object];
}

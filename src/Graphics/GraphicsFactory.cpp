#include "Graphics/GraphicsCreature.h"
#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsItem.h"

QHash <const Object *, GraphicsObject *> GraphicsFactory::map_;

GraphicsObject * GraphicsFactory::get(Object *object)
{
	GraphicsObject *graphicsObject;
	const Object *constObject = (const Object *)object;
	if (!map_.contains(constObject)) {
		switch (object->objectType()) {
		case HOA::ObjectType::Creature:
			graphicsObject = new GraphicsCreature((Creature *)object);
			break;
		case HOA::ObjectType::Item:
			graphicsObject = new GraphicsItem((Item *)object);
			break;
		default:
			Q_ASSERT(false);
		}
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

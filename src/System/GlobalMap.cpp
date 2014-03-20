#include "System/GlobalMap.h"

GlobalMap::GlobalMap(int width, int height)
	: Map(width, height)
{}

QVector <Town *> GlobalMap::towns() const
{
	QVector <Town *> ts;
	for (Object *obj : objects_)
		if (obj->objectType() == HOA::ObjectType::Town)
			ts.append((Town *)obj);
	return ts;
}
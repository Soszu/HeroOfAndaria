#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <QtWidgets>
#include "Graphics/GraphicsBlacksmith.h"
#include "Graphics/GraphicsInn.h"
#include "Graphics/GraphicsMap.h"
#include "Graphics/GraphicsObject.h"
#include "Graphics/GraphicsPlace.h"

class GraphicsFactory
{
public:
	static GraphicsObject * get(Object *object);
	static GraphicsObject * get(const Object *object);

	static GraphicsPlace * get(Place *place);

	static GraphicsMap * get(Map *map);

	static GraphicsItem * get(Item *item);//TODO

private:
	GraphicsFactory() = delete;
	GraphicsFactory(const GraphicsFactory &) = delete;

	static QHash <const Object *, GraphicsObject *> map_;
	static QHash <Place *, GraphicsPlace *> placesMap_;
	static QHash <Map *, GraphicsMap *> mapsMap_;
};

#endif // GRAPHICSFACTORY_H

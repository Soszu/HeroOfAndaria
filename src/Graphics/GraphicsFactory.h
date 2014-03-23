#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "Graphics/GraphicsPlace.h"
#include "System/Object.h"
#include "System/Place.h"
#include "Graphics/GraphicsBlacksmith.h"
#include "Graphics/GraphicsInn.h"

class GraphicsFactory
{
public:
	static GraphicsObject * get(Object *object);
	static GraphicsObject * get(const Object *object);
	static GraphicsPlace * get(Place * place);
private:
	GraphicsFactory() = delete;
	GraphicsFactory(const GraphicsFactory &) = delete;
	
	static QHash <const Object *, GraphicsObject *> map_;
};

#endif // GRAPHICSFACTORY_H

#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <QtWidgets>
#include "Graphics/GraphicsObject.h"
#include "System/Object.h"

class GraphicsFactory
{
public:
	static GraphicsObject * get(Object *object);
	static GraphicsObject * get(const Object *object);

private:
	GraphicsFactory() = delete;
	GraphicsFactory(const GraphicsFactory &) = delete;

	static QHash <const Object *, GraphicsObject *> map_;
};

#endif // GRAPHICSFACTORY_H

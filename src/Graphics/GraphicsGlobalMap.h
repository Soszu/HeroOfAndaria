#ifndef GRAPHICSGLOBALMAP_H
#define GRAPHICSGLOBALMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsMap.h"
#include "System/GlobalMap.h"

class GraphicsGlobalMap : public GraphicsMap
{
public:
	GraphicsGlobalMap(GlobalMap *map);
};

#endif // GRAPHICSGLOBALMAP_H

#ifndef GRAPHICSLOCALMAP_H
#define GRAPHICSLOCALMAP_H

#include "Graphics/GraphicsMap.h"
#include "System/LocalMap.h"

class GraphicsLocalMap : public GraphicsMap
{
public:
	GraphicsLocalMap(LocalMap *map);
};

#endif // GRAPHICSLOCALMAP_H

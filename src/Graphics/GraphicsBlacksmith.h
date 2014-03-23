#ifndef GRAPHICSBLACKSMITH_H
#define GRAPHICSBLACKSMITH_H

#include "Graphics/GraphicsEquipmentExchange.h"
#include "Graphics/GraphicsPlace.h"
#include "System/Blacksmith.h"
#include "System/Place.h"

class GraphicsBlacksmith : public GraphicsPlace, public GraphicsEquipmentExchange
{
	Q_OBJECT;
public:
	GraphicsBlacksmith(Blacksmith * blacksmith, QWidget * parent = 0);
};

#endif // GRAPHICSBLACKSMITH_H

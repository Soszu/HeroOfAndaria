#ifndef GRAPHICSBLACKSMITH_H
#define GRAPHICSBLACKSMITH_H

#include "Graphics/GraphicsEquipmentExchange.h"
#include "Graphics/GraphicsPlace.h"
#include "System/Blacksmith.h"
#include "System/Place.h"
/*
 * Graphics Blacksmith nie moze dziedzyc po GraphicsPlace i GraphicsEquipmentExchange
 * jednoczesnie, nie mozna dziedziczyc po 2 QObjectach :( 
 */

class GraphicsBlacksmith : public GraphicsPlace
{
	Q_OBJECT;
public:
	GraphicsBlacksmith(Blacksmith * blacksmith, QWidget * parent = 0);
private:
	GraphicsEquipmentExchange *eqWidget_;
};

#endif // GRAPHICSBLACKSMITH_H

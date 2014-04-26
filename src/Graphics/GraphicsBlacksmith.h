#ifndef GRAPHICSBLACKSMITH_H
#define GRAPHICSBLACKSMITH_H

#include "Graphics/GraphicsEquipmentExchange.h"
#include "Graphics/GraphicsPlace.h"
#include "System/Blacksmith.h"
#include "System/Place.h"

class GraphicsBlacksmith : public GraphicsPlace
{
Q_OBJECT;
public:
	GraphicsBlacksmith(Blacksmith *blacksmith, QWidget *parent = nullptr);

private:
	GraphicsEquipmentExchange *eqWidget_;
};

#endif // GRAPHICSBLACKSMITH_H

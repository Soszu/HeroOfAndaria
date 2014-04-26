#include "Graphics/GraphicsBlacksmith.h"

GraphicsBlacksmith::GraphicsBlacksmith(Blacksmith *blacksmith, QWidget *parent) :
	GraphicsPlace((Place *)blacksmith, parent)
{
	//TEMP
	EquipmentCarrier *a = new EquipmentCarrier();
	EquipmentCarrier *b = new EquipmentCarrier();
	GraphicsEquipment *gEa = new GraphicsEquipment(a, 3, this);
	GraphicsEquipment *gEb = new GraphicsEquipment(b, 3, this);
	this->eqWidget_ = new GraphicsEquipmentExchange(gEa, gEb);


	this->layout()->addWidget(this->eqWidget_);
}

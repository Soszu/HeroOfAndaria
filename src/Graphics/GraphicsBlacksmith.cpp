#include "Graphics/GraphicsBlacksmith.h"

GraphicsBlacksmith::GraphicsBlacksmith(Blacksmith *blacksmith, QWidget *parent) :
	GraphicsPlace((Place *)blacksmith, parent)
{
	//TEMP
	EquipmentCarrier *a = new EquipmentCarrier();
	EquipmentCarrier *b = new EquipmentCarrier();
	Weapon **w = new Weapon* [100];
	for (int i = 0; i < 100; i++) {
		w[i] = new Weapon();
		a->addItem(w[i]);
	}
	GraphicsEquipment *gEa = new GraphicsEquipment(a, 5, this);
	GraphicsEquipment *gEb = new GraphicsEquipment(b, 5, this);
	this->eqWidget_ = new GraphicsEquipmentExchange(gEa, gEb);


	this->layout()->addWidget(this->eqWidget_);

	this->layout()->setAlignment(this->eqWidget_, Qt::AlignHCenter);
	this->backgroundImage_ = DataManager::pixmap(Data::ImagePath::BlacksmithBackground);
}

void GraphicsBlacksmith::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.drawPixmap(rect(), *(this->backgroundImage_));

	this->QWidget::paintEvent(event);
}



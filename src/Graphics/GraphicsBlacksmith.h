#ifndef GRAPHICSBLACKSMITH_H
#define GRAPHICSBLACKSMITH_H

#include "Graphics/GraphicsEquipmentExchange.h"
#include "Graphics/GraphicsPlace.h"
#include "System/Blacksmith.h"
#include "System/Place.h"
#include "System/Weapon.h"
#include "System/DataManager.h"
#include "System/Paths.h"


class GraphicsBlacksmith : public GraphicsPlace
{
Q_OBJECT;
public:
	GraphicsBlacksmith(Blacksmith *blacksmith, QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event);

private:
	GraphicsEquipmentExchange *eqWidget_;
	QPixmap *backgroundImage_;
};

#endif // GRAPHICSBLACKSMITH_H

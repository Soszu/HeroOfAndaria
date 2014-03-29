#ifndef GRAPHICSGLOBALMAP_H
#define GRAPHICSGLOBALMAP_H

#include <QtWidgets>
#include "Graphics/GraphicsMap.h"
#include "System/GlobalMap.h"

class GraphicsGlobalMap : public GraphicsMap
{
Q_OBJECT;

public:
	GraphicsGlobalMap(GlobalMap *map);

private:
	QWidget *mapWidget_;
	QWidget *townWidget_;

	static const int MAP_INDEX  = 0;
	static const int TOWN_INDEX = 1;

	void initMap();
	void initLayout();

	void keyPressEvent(QKeyEvent *event);

	void tryEnterTown();

private slots:
	void onTownEntered();
	void onTownExited();
};

#endif // GRAPHICSGLOBALMAP_H

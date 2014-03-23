#ifndef GRAPHICSINN_H
#define GRAPHICSINN_H

#include <QtWidgets>
#include "Graphics/GraphicsPlace.h"
#include "System/Inn.h"

class GraphicsInn : public GraphicsPlace
{
	Q_OBJECT;
public:
	GraphicsInn(Inn * inn, QWidget * parent = 0);
};

#endif // GRAPHICSINN_H

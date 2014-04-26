#ifndef GRAPHICSPLACE_H
#define GRAPHICSPLACE_H

#include "System/Place.h"
#include <QtWidgets>

class GraphicsPlace : public QWidget
{
Q_OBJECT;

public:
	GraphicsPlace(Place * p, QWidget * parent = 0);
	QPushButton* exitButton();
	QVBoxLayout * layout();
private:
	Place * place_;
	QVBoxLayout * layout_;
	QPushButton * exitButton_;

};

#endif // GRAPHICSPLACE_H

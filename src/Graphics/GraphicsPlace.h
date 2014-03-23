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
private:
	Place * place_;
	QHBoxLayout * layout_;
	QPushButton * exitButton_;

};

#endif // GRAPHICSPLACE_H

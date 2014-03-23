#include "Graphics/GraphicsPlace.h"

GraphicsPlace::GraphicsPlace(Place * p, QWidget * parent) :
	QWidget(parent),
	place_(p),
	layout_(new QHBoxLayout(this)),
	exitButton_(new QPushButton("exit"))
{
	this->layout_->addWidget(this->exitButton_);
}

QPushButton * GraphicsPlace::exitButton()
{
	return this->exitButton_;
}


/*
GraphicsPlace::~GraphicsPlace()
{

}

*/
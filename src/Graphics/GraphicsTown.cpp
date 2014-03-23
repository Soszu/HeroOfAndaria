#include "Graphics/GraphicsTown.h"
#include "Graphics/GraphicsFactory.h"

GraphicsTown::GraphicsTown(Town * town, QWidget * parent) :
	QStackedWidget(parent),
	town_(town)
{
	
	QVector<QString> buttonCaps;
	for (Place * p : town_->places()) {
		buttonCaps.append(p->name());
		placeMap_.insert(p->name(), p);
		
		GraphicsPlace * gp = GraphicsFactory::get(p);
		gp->setParent(this);
		this->addWidget(gp);
		connect(gp->exitButton(), &QPushButton::clicked, this, &GraphicsTown::exitPlace);
		widgetMap_.insert(p->name(), gp);
	}
	
	this->mainView_ = new TownMainView(buttonCaps, this);
	connect(this->mainView_->sigMapper(), static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &GraphicsTown::enter);
	
	connect(this->mainView_->exitButton(), &QPushButton::clicked, this, &GraphicsTown::exitTown);
	
	this->addWidget(this->mainView_);
	
	this->setCurrentWidget(this->mainView_);
}

void GraphicsTown::enter(const QString & name)
{
	this->town_->visitPlace(placeMap_.value(name));
	this->setCurrentWidget(widgetMap_.value(name));
}

void GraphicsTown::exitPlace()
{
	this->setCurrentWidget(this->mainView_);
}

void GraphicsTown::exitTown()
{
	emit this->leaveTown();
}


TownMainView::TownMainView(QVector <QString> &buttonCaps, QWidget * parent) :
	QWidget(parent),
	layout_(new QHBoxLayout(this)),
	sigMapper_(new QSignalMapper(this)),
	exitButton_(new QPushButton("leaveTown"))
{
	for (QString cap : buttonCaps) {
		QPushButton * butt = new QPushButton(cap);
		layout_->addWidget(butt);
		sigMapper_->setMapping(butt, cap);
		connect(butt, SIGNAL(clicked()), sigMapper_, SLOT(map()));
	}
	layout_->addWidget(this->exitButton_);
	
}
QPushButton* TownMainView::exitButton()
{
	return this->exitButton_;
}


QSignalMapper* TownMainView::sigMapper()
{
	return this->sigMapper_;
}

GraphicsTown* getExample()
{
	Town * town = new Town();
	Blacksmith * bl = new Blacksmith("Kowal");
	Inn * inn = new Inn("Gospoda");
	town->addPlace(bl);
	town->addPlace(inn);
	
	return new GraphicsTown(town);
	
}

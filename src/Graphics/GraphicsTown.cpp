#include "Graphics/GraphicsTown.h"

GraphicsTown::GraphicsTown(QWidget * parent, Town * town)
	: QWidget(parent),
	town_(town),
	layout_(new QHBoxLayout(this)),
	sigMapper_(new QSignalMapper(this))
{
	connect(sigMapper_, SIGNAL(mapped(QString)), this, SLOT(enter(QString)));
	for (Place * p : town_->places()) {
		QPushButton * butt = new QPushButton(p->name());
		layout_->addWidget(butt);
		sigMapper_->setMapping(butt, p->name());
		placeMapper_.insert(p->name(), p);
		connect(butt, SIGNAL(clicked()), sigMapper_, SLOT(map()));
	}
}

void GraphicsTown::enter(const QString & name)
{
	this->town_->visitPlace(placeMapper_.value(name));
}

#include "Graphics/GraphicsTown.h"
#include "Graphics/GraphicsFactory.h"
#include <System/Paths.h>
#include <iostream>

GraphicsTown::GraphicsTown(Town *town, QWidget *parent) :
	QStackedWidget(parent),
	town_(town)
{
	QVector <QPair <QString, HOA::PlaceType> > buttonCaps;
	for (Place *p : town_->places()) {
		buttonCaps.append({p->name(), p->type()});
		placeMap_.insert(p->name(), p);

		GraphicsPlace *gp = GraphicsFactory::get(p);
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

void GraphicsTown::enter(const QString &name)
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
	town_->exitTown();
}

/*		TownMainView		*/

TownMainView::TownMainView(QVector <QPair <QString, HOA::PlaceType> > &buttonCaps, QWidget *parent) :
	QWidget(parent),
	layout_(new QHBoxLayout(this)),
	sigMapper_(new QSignalMapper(this)),
	exitButton_(new PlaceButton(new QPixmap(Data::path(Data::ImagePath::LeaveTownButton)),
	                            new QPixmap(Data::path(Data::ImagePath::OpenPlaceButton)), QString("Wyjdź"), this))
{
	for (auto desc : buttonCaps) {
		QString closedPath;
		QString openPath = Data::path(Data::ImagePath::OpenPlaceButton);
		switch (desc.second){
			case HOA::PlaceType::Blacksmith:
				closedPath = Data::path(Data::ImagePath::BlacksmithButton);
				break;
			case HOA::PlaceType::Inn:
				closedPath = Data::path(Data::ImagePath::InnButton);
				break;
			default:
				break;
		}
		QPixmap *closedImage = new QPixmap(closedPath);
		QPixmap *openImage = new QPixmap(openPath);
		PlaceButton *butt = new PlaceButton(closedImage, openImage, desc.first, this);
		layout_->addWidget(butt);
		sigMapper_->setMapping(butt, desc.first);
		connect(butt, SIGNAL(clicked()), sigMapper_, SLOT(map())); //TODO change this
	}
	layout_->addWidget(this->exitButton_);

	this->backgroundImage_.load(Data::path(Data::ImagePath::TownBackground));

}

void TownMainView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.drawPixmap(rect(), this->backgroundImage_);

	this->QWidget::paintEvent(event);
}


QPushButton * TownMainView::exitButton()
{
	return this->exitButton_;
}


QSignalMapper * TownMainView::sigMapper()
{
	return this->sigMapper_;
}

/*		PlaceButton		*/

PlaceButton::PlaceButton(QPixmap *closedImage, QPixmap *openImage, QString text, QWidget *parent) :
	QPushButton(text, parent),
	closedImage_(closedImage),
	openImage_(openImage),
	fontPointSize_(DEFAULT_FONT_SIZE),
	isMouseOver_(false)
{
	setMouseTracking(true);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

}

void PlaceButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (!this->isMouseOver_)
		painter.drawPixmap(rect(), *(this->closedImage_));
	else
		painter.drawPixmap(rect(), *(this->openImage_));
	QFont font = QApplication::font();
	font.setPointSize(fontPointSize_);

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}

QSize PlaceButton::minimumSize() const
{
	return QSize(closedImage_->width(), closedImage_->height());
}

QSize PlaceButton::sizeHint() const
{
	return QSize(closedImage_->width(), closedImage_->height());
}

void PlaceButton::enterEvent(QEvent* event)
{
	isMouseOver_ = true;
}
void PlaceButton::leaveEvent(QEvent* event)
{
	isMouseOver_ = false;
}

/**
 * \class GraphicsTownObject
 */

GraphicsTownObject::GraphicsTownObject(Town *town)
	: GraphicsObject(town)
{
	graphicsTown_ = new GraphicsTown(town);
	//TODO graphicsTown_->setParent(this);
	pixmap_ = QPixmap(Data::path(Data::ImagePath::TownPoor));
}

GraphicsTown * GraphicsTownObject::graphicsTown()
{
	return graphicsTown_;
}

QRectF GraphicsTownObject::boundingRect() const
{
	qreal width  = (qreal)pixmap_.width();
	qreal height = (qreal)pixmap_.height();
	return {-width / 2, -height / 2, width, height};
}

void GraphicsTownObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
// 	painter->save();

	painter->setPen(Qt::black);

// 	painter->drawRect(boundingRect().toRect());

// 	painter->drawPixmap(QRect(0, 0, pixmap_.width(), pixmap_.height()), pixmap_);
	painter->drawPixmap(boundingRect().toRect(), pixmap_);

// 	painter->restore();
}

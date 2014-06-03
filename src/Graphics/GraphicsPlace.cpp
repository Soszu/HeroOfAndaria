#include "Graphics/GraphicsPlace.h"

GraphicsPlace::GraphicsPlace(Place * p, QWidget * parent) :
	QWidget(parent),
	place_(p),
	layout_(new QVBoxLayout(this)),
	exitButton_(new ExitPlaceButton())
{
	this->layout_->addWidget(this->exitButton_);
	this->layout_->setAlignment(this->exitButton_, Qt::AlignHCenter);
}

QPushButton * GraphicsPlace::exitButton()
{
	return this->exitButton_;
}

QVBoxLayout * GraphicsPlace::layout()
{
	return this->layout_;
}

ExitPlaceButton::ExitPlaceButton(QWidget *parent) :
	QPushButton("", parent),
	focusImage_(DataManager::pixmap(Data::ImagePath::ExitPlaceButtonFocus)),
	noFocusImage_(DataManager::pixmap(Data::ImagePath::ExitPlaceButtonNoFocus)),
	fontPointSize_(DEFAULT_FONT_SIZE),
	isMouseOver_(false)
{
	setMouseTracking(true);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ExitPlaceButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (!this->isMouseOver_)
		painter.drawPixmap(rect(), *(this->noFocusImage_));
	else
		painter.drawPixmap(rect(), *(this->focusImage_));
	QFont font = QApplication::font();
	font.setPointSize(fontPointSize_);

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}

QSize ExitPlaceButton::minimumSize() const
{
	return QSize(noFocusImage_->width(), noFocusImage_->height());
}

QSize ExitPlaceButton::sizeHint() const
{
	return QSize(noFocusImage_->width(), noFocusImage_->height());
}

void ExitPlaceButton::enterEvent(QEvent* event)
{
	isMouseOver_ = true;
}
void ExitPlaceButton::leaveEvent(QEvent* event)
{
	isMouseOver_ = false;
}


/*
GraphicsPlace::~GraphicsPlace()
{

}

*/

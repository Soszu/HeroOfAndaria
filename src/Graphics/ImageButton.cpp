#include "ImageButton.h"
#include "System/Paths.h"

/* ---------------  ImageButton class -------------------------- */

ImageButton::ImageButton(QPixmap normalImage, QPixmap darkImage, QString text, QWidget *parent) :
	QPushButton(text, parent),
	normalImage_(normalImage),
	darkImage_(darkImage),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ImageButton::ImageButton(ImageButtonType type, QString text, QWidget *parent) :
	QPushButton(text, parent),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	switch (type) {
		case MENU_BUTTON:
			normalImage_.load(Data::Images::MenuButtonsNormal);
			darkImage_.load(Data::Images::MenuButtonsDark);
			break;
		case SMALL_MENU_BUTTON:
			normalImage_.load(Data::Images::SmallMenuButtonNormal);
			darkImage_.load(Data::Images::SmallMenuButtonDark);
			break;
		case NEXT_ARROW_BUTTON:
			normalImage_.load(Data::Images::NextButtonNormal);
			darkImage_.load(Data::Images::NextButtonDark);
			break;
		case PREV_ARROW_BUTTON:
			normalImage_.load(Data::Images::PrevButtonNormal);
			darkImage_.load(Data::Images::PrevButtonDark);
			break;
		case UP_MENU_BUTTON:
			normalImage_.load(Data::Images::UpButtonNormal);
			darkImage_.load(Data::Images::UpButtonDark);
			break;
		case DOWN_MENU_BUTTON:
			normalImage_.load(Data::Images::DownButtonNormal);
			darkImage_.load(Data::Images::DownButtonDark);
			break;
	}
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ImageButton::setFontPointSize(int value)
{
	fontPointSize_ = value;
}

QSize ImageButton::sizeHint() const
{
	return QSize(normalImage_.width(), normalImage_.height());
}

void ImageButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (isDown() || !isEnabled())
		painter.drawPixmap(rect(), darkImage_);
	else
		painter.drawPixmap(rect(), normalImage_);

	QFont font = QApplication::font();
	font.setPointSize(fontPointSize_);
	if (hasFocus())
		font.setBold(true);

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}

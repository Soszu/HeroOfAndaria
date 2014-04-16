#include "Graphics/ImageButton.h"
#include "System/DataManager.h"
#include "System/Paths.h"

/* ---------------  ImageButton class -------------------------- */

ImageButton::ImageButton(QString normalPath, QString darkPath, QString text, QWidget *parent) :
	QPushButton(text, parent),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	loadImages(normalPath, darkPath);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ImageButton::ImageButton(ImageButtonType type, QString text, QWidget *parent) :
	QPushButton(text, parent),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	switch (type) {
		case MENU_BUTTON:
			loadImages(Data::path(Data::ImagePath::MenuButtonsNormal),
			           Data::path(Data::ImagePath::MenuButtonsDark));
			break;
		case SMALL_MENU_BUTTON:
			loadImages(Data::path(Data::ImagePath::SmallMenuButtonNormal),
			           Data::path(Data::ImagePath::SmallMenuButtonDark));
			break;
		case NEXT_ARROW_BUTTON:
			loadImages(Data::path(Data::ImagePath::NextButtonNormal),
			           Data::path(Data::ImagePath::NextButtonDark));
			break;
		case PREV_ARROW_BUTTON:
			loadImages(Data::path(Data::ImagePath::PrevButtonNormal),
			           Data::path(Data::ImagePath::PrevButtonDark));
			break;
		case UP_MENU_BUTTON:
			loadImages(Data::path(Data::ImagePath::UpButtonNormal),
			           Data::path(Data::ImagePath::UpButtonDark));
			break;
		case DOWN_MENU_BUTTON:
			loadImages(Data::path(Data::ImagePath::DownButtonNormal),
			           Data::path(Data::ImagePath::DownButtonDark));
			break;
	}
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ImageButton::loadImages(const QString normalPath, const QString darkPath)
{
	normalImage_ = DataManager::pixmap(normalPath);
	darkImage_ = DataManager::pixmap(darkPath);
}

void ImageButton::setFontPointSize(int value)
{
	fontPointSize_ = value;
}

QSize ImageButton::sizeHint() const
{
	return QSize(normalImage_->width(), normalImage_->height());
}

void ImageButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (isDown() || !isEnabled())
		painter.drawPixmap(rect(), *darkImage_);
	else
		painter.drawPixmap(rect(), *normalImage_);

	QFont font = QApplication::font();
	font.setPointSize(fontPointSize_);
	if (hasFocus())
		font.setBold(true);

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}

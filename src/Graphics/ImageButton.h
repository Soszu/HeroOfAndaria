#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QApplication>

class ImageButton : public QPushButton
{
Q_OBJECT;
public:
	enum ImageButtonType : quint8 {
		MENU_BUTTON,
		SMALL_MENU_BUTTON,
		NEXT_ARROW_BUTTON,
		PREV_ARROW_BUTTON,
		UP_MENU_BUTTON,
		DOWN_MENU_BUTTON
	};

	ImageButton(QString normalPath, QString darkPath, QString text = "", QWidget *parent = 0);
	ImageButton(ImageButtonType type, QString text = "", QWidget *parent = 0);
	void setFontPointSize(int value);
	QSize sizeHint() const;

private:
	QPixmap *normalImage_;
	QPixmap *darkImage_;

	int fontPointSize_;
	static const int DEFAULT_FONT_SIZE = 11;


protected:
	void loadImages(const QString normalPath, const QString darkPath);
	void paintEvent(QPaintEvent *);
	QPixmap *normalImage();
	QPixmap *darkImage();
	int fontPointSize();

};

#endif // IMAGE_BUTTON_H

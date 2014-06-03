#ifndef GRAPHICSPLACE_H
#define GRAPHICSPLACE_H

#include "System/Place.h"
#include "System/Paths.h"
#include "System/DataManager.h"
#include <QtWidgets>

class ExitPlaceButton;

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
	ExitPlaceButton * exitButton_;

};

class ExitPlaceButton : public QPushButton
{
Q_OBJECT;

public:
	ExitPlaceButton(QWidget *parent = 0);

	QSize minimumSize() const;
	QSize sizeHint() const;
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
protected:
	void paintEvent(QPaintEvent *event);

private:
	QPixmap *focusImage_;
	QPixmap *noFocusImage_;
	int fontPointSize_;
	static const int DEFAULT_FONT_SIZE = 11;
	bool isMouseOver_;
};


#endif // GRAPHICSPLACE_H

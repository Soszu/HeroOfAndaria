#ifndef GRAPHICSTOWN_H
#define GRAPHICSTOWN_H

#include <QtWidgets>
#include "Graphics/GraphicsPlace.h"
#include "Graphics/GraphicsObject.h"
#include "System/Town.h"

class TownMainView;

class GraphicsTown : public QStackedWidget
{
Q_OBJECT;

public:
	GraphicsTown(Town *town, QWidget *parent = nullptr);

	Town *town() const;

private:
	TownMainView *mainView_;
	Town *town_;
	QVector <QPushButton *> buttons_;
	QMap <QString, Place *> placeMap_;
	QMap <QString, GraphicsPlace *>	widgetMap_;

private slots:
	void enter(const QString &name);
	void exitPlace();
	void exitTown();
};

class TownMainView : public QWidget
{
Q_OBJECT;

public:
	TownMainView(QVector <QPair <QString, HOA::PlaceType> > &buttonCaps, QWidget *parent = 0);
	QSignalMapper *sigMapper();
	QPushButton *exitButton();

protected:
	void paintEvent(QPaintEvent *event);

private:
	QHBoxLayout *layout_;
	QSignalMapper *sigMapper_;
	QPushButton *exitButton_;

	QPixmap *backgroundImage_;
};

class PlaceButton : public QPushButton
{
Q_OBJECT;

public:
	PlaceButton(QPixmap *closedImage, QPixmap *openImage, QString text, QWidget *parent);

	QSize minimumSize() const;
	QSize sizeHint() const;
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
protected:
	void paintEvent(QPaintEvent *event);

private:
	QPixmap *closedImage_;
	QPixmap *openImage_;
	int fontPointSize_;
	static const int DEFAULT_FONT_SIZE = 11;
	bool isMouseOver_;
};

/**
 * \class GraphicsTownObject
 * Graphical representation of a town on the global map.
 */
class GraphicsTownObject : public GraphicsObject
{
public:
	GraphicsTownObject(Town *town);

	GraphicsTown *graphicsTown();

private:
	GraphicsTown *graphicsTown_;

	QPixmap *pixmap_;

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // GRAPHICSTOWN_H

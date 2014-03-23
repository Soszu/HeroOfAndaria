#ifndef GRAPHICSTOWN_H
#define GRAPHICSTOWN_H

#include <QtWidgets>
#include "System/Town.h"
#include <QMap>
#include <QString>
#include <QVector>
#include "Graphics/GraphicsPlace.h"

class TownMainView;

class GraphicsTown : public QStackedWidget
{
	Q_OBJECT;
public:
	GraphicsTown(Town * town, QWidget * parent = 0);
	
private:
	
	TownMainView * mainView_;
	Town * town_;
	QVector <QPushButton *> buttons_;
	QMap <QString, Place *> placeMap_;
	QMap <QString, GraphicsPlace *>	widgetMap_;
private slots:
	void enter(const QString & name);
	void exitPlace();
	void exitTown();
signals:
	void leaveTown();
	
};

class TownMainView : public QWidget
{
	Q_OBJECT;
public:
	TownMainView(QVector< QString >& buttonCaps, QWidget* parent = 0);
	QSignalMapper * sigMapper();
	QPushButton * exitButton();
private:
	QHBoxLayout * layout_;
	QSignalMapper * sigMapper_;
	QPushButton * exitButton_;
};


GraphicsTown * getExample();

#endif // GRAPHICSTOWN_H

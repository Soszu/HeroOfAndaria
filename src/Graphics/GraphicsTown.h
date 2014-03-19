#ifndef GRAPHICSTOWN_H
#define GRAPHICSTOWN_H

#include <QtWidgets>
#include "System/Town.h"
#include <QMap>
class GraphicsTown : public QWidget
{
	Q_OBJECT;
public:
	GraphicsTown(QWidget * parent, Town * town);
	
private:
	Town * town_;
	QHBoxLayout * layout_;
	QSignalMapper * sigMapper_;
	QVector <QPushButton *> buttons_;
	QMap <QString, Place *> placeMapper_;
private slots:
	void enter(const QString & name);
};

#endif // GRAPHICSTOWN_H

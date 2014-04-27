#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <QtWidgets>
#include <QSvgRenderer>
#include "Paths.h"

class DataManager
{
public:
	static QPixmap * pixmap(const QString &path);
	static QPixmap * pixmap(Data::ImagePath name);
	static QSvgRenderer * renderer(const QString &path);
	static QSvgRenderer * renderer(Data::ImagePath name);

private:
	DataManager() = delete;
	DataManager(const DataManager &) = delete;

	static QHash <QString, QPixmap *> pixmapsMap;
	static QHash <QString, QSvgRenderer *> renderersMap;
};

#endif // DATA_MANAGER_H

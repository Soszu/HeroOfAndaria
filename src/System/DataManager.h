#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <QtWidgets>
#include "Paths.h"

class DataManager
{
public:
	static QPixmap * pixmap(const QString &path);
	static QPixmap * pixmap(Data::ImagePath name);

private:
	DataManager() = delete;
	DataManager(const DataManager &) = delete;

	static QHash <QString, QPixmap *> pixmapsMap;
};

#endif // DATA_MANAGER_H

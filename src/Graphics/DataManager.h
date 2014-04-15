#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <QtWidgets>

class DataManager
{
public:
	static QPixmap * getPixmap(const QString &path);

private:
	DataManager() = delete;
	DataManager(const DataManager &) = delete;

	static QHash <QString, QPixmap *> pixmapsMap;
};

#endif // DATA_MANAGER_H

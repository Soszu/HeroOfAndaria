#include "DataManager.h"

QHash <QString, QPixmap *> DataManager::pixmapsMap;

QPixmap * DataManager::pixmap(const QString &path)
{
	if (!pixmapsMap.contains(path)) {
		QPixmap *image = new QPixmap();
		if (!image->load(path)) {
			qCritical() << "Error wihile loading file " << path;
			exit(EXIT_FAILURE);
		}
		pixmapsMap[path] = image;
	}
	return pixmapsMap[path];
}

QPixmap * DataManager::pixmap(Data::ImagePath name)
{
	return pixmap(Data::path(name));
}



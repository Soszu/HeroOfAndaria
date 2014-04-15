#include "DataManager.h"

QHash <QString, QPixmap *> DataManager::pixmapsMap;

QPixmap * DataManager::getPixmap(const QString &path)
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


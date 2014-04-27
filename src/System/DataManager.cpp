#include "DataManager.h"

QHash <QString, QPixmap *> DataManager::pixmapsMap;
QHash <QString, QSvgRenderer *> DataManager::renderersMap;

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

QSvgRenderer * DataManager::renderer(const QString &path)
{
	if (!renderersMap.contains(path)) {
		QSvgRenderer *render = new QSvgRenderer();
		if (!render->load(path)) {
			qCritical() << "Error wihile loading file " << path;
			exit(EXIT_FAILURE);
		}
		renderersMap[path] = render;
	}
	return renderersMap[path];
}

QSvgRenderer * DataManager::renderer(Data::ImagePath name)
{
	return renderer(Data::path(name));
}

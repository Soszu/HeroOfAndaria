#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <QtCore>

template <typename T>
bool loadFromFile(T &obj, const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QDataStream input(&file);
	input >> obj;

	return true;
}

template <typename T>
bool saveToFile(T &obj, const QString &fileName)
{
	QTemporaryFile tmpFile;

	if (!tmpFile.open())
		return false;

	QDataStream output(&tmpFile);
	output << obj;

	if (!tmpFile.flush())
		return false;
	tmpFile.close();

	if (QFile::exists(fileName)) {
		if (QFile::exists(fileName + '~'))
			QFile::remove(fileName + '~');
		if (!QFile::copy(fileName, fileName + '~') || !QFile::remove(fileName))
			return false;
	}

	if (!tmpFile.copy(fileName))
		return false;

	return true;
}

#endif

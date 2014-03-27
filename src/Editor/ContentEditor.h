#ifndef CONTENTEDITOR_H
#define CONTENTEDITOR_H

#include <QtWidgets>

class ContentEditor : public QObject
{
Q_OBJECT

public:
	ContentEditor(const QString &name);

	QString name() const;
	QWidget * widget() const;

	virtual void clear(){}
	virtual bool isChanged() const = 0;
	virtual void saveToStream(QDataStream &out) const = 0 ;
	virtual void loadFromStream(QDataStream &in) = 0;

public slots:
	virtual void modelSaved() = 0;

protected:
	QWidget *widget_;
	QString name_;
};

#endif // CONTENTEDITOR_H

#ifndef GRAPHICSEQUIPMENTEXCHANGE_H
#define GRAPHICSEQUIPMENTEXCHANGE_H
#include "System/EquipmentCarrier.h"
#include "GraphicsItem.h"
#include "ImageButton.h"
#include <QtWidgets>

class GraphicsEquipment;
class SlotButton;

class GraphicsEquipmentExchange : public QWidget
{
Q_OBJECT;
public:
	GraphicsEquipmentExchange(GraphicsEquipment *l, GraphicsEquipment *r);
	GraphicsEquipmentExchange();
private:
	GraphicsEquipment *l_;
	GraphicsEquipment *r_;
	GraphicsEquipment *active_;
	ImageButton *exchangeButton_;
	void setActive(GraphicsEquipment *active);
	GraphicsEquipment *notActive();
	QVBoxLayout *layout_;
	QHBoxLayout *GElayout_;
private slots:
	void exchange();
signals:
	void sigReset();
};

class GraphicsEquipment : public QWidget
{
Q_OBJECT;
public:
	GraphicsEquipment(EquipmentCarrier *eq, int span, QWidget *parent = 0);
	EquipmentCarrier *eq();
	SlotButton *activeSlot();
private:
	EquipmentCarrier *eq_;
	QVector <SlotButton *> gButtons_;
	SlotButton *activeSlot_;

	QGridLayout *layout_;
	QSignalMapper *buttonMapper_;
	void addSlot(GraphicsItem *gi);
	int span_;
	void rearangeSlots();
protected:
	void paintEvent(QPaintEvent *event);
public slots:
	void processClick(QWidget *sB);
	bool receiveItem(GraphicsEquipment *from, GraphicsItem *item);
	void removeItem(SlotButton *sb);
	void reset();
signals:
	void sigReset();
	void sigActive(GraphicsEquipment * gE);
};

class SlotButton : public ImageButton
{
Q_OBJECT;
public:
	SlotButton(QWidget *parent = 0);
	SlotButton(GraphicsItem *gi, QWidget *parent = 0);

	GraphicsItem *gItem();
	void setGItem(GraphicsItem *gi);
private:
	GraphicsItem *gItem_;
};

#endif // GRAPHICSEQUIPMENTEXCHANGE_H

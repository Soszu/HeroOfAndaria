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
	QVBoxLayout *layout_;
	QHBoxLayout *GElayout_;
	QScrollArea *rscrollarea_;
	QScrollArea *lscrollarea_;

	void setActive(GraphicsEquipment *active);
	GraphicsEquipment * notActive();

private slots:
	void exchange();

signals:
	void sigReset();
};

class GraphicsEquipment : public QWidget
{
Q_OBJECT;
public:
	GraphicsEquipment(EquipmentCarrier *eq, int span, QWidget *parent = nullptr);
	EquipmentCarrier * eq();
	SlotButton * activeSlot();
	int span();
	QSize sizeHint() const;
private:
	EquipmentCarrier *eq_;
	QVector <SlotButton *> gButtons_;
	SlotButton *activeSlot_;

	QGridLayout *layout_;
	QSignalMapper *buttonMapper_;

	int span_;

	void addSlot(GraphicsItem *gi);
	void rearrangeSlots();

protected:
	//void paintEvent(QPaintEvent *event);

public slots:
	void processClick(QWidget *sB);
	bool receiveItem(GraphicsEquipment *from, GraphicsItem *item);
	void removeItem(SlotButton *sb);
	void reset();

signals:
	void sigReset();
	void sigActive(GraphicsEquipment *gE);
};

class SlotButton : public ImageButton
{
Q_OBJECT;
public:
	SlotButton(QWidget *parent = nullptr);
	SlotButton(GraphicsItem *gi, QWidget *parent = nullptr);

	GraphicsItem *gItem();
	void setGItem(GraphicsItem *gi);

private:
	void paintEvent(QPaintEvent *event);
	GraphicsItem *gItem_;
};

#endif // GRAPHICSEQUIPMENTEXCHANGE_H

#ifndef PANEL_H
#define PANEL_H

#include <QtWidgets>
#include "ImageButton.h"

class HPBar;
class Creature;
class Character;

/* ----------------------- Panel class ------------------ */

class Panel : public QWidget
{
Q_OBJECT;
public:
	Panel(QWidget *parent = 0);
	QSize sizeHint() const;

signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event);
	QPixmap *backgroundImage;

};

/* ---------------------- BottomPanel class -------------- */

class BottomPanel : public Panel
{
Q_OBJECT;
public:
	BottomPanel(Character *player, QWidget *parent = 0);

private:
	ImageButton *inventoryButton;
	ImageButton *skillsButton;
	ImageButton *questsButton;

	HPBar *hpBar;

signals:
	void inventoryPressed();
	void skillsPressed();
	void questsPressed();

};

/* -------------------- SidePanel class ----------------- */

class SidePanel : public Panel
{
Q_OBJECT;
public:
	SidePanel(QWidget *parent = 0);

private:
	ImageButton *exitButton;
	QLabel *label;

	static const int INVENTORY_PANEL_INDEX = 0;
	static const int SKILLS_PANEL_INDEX = 1;
	static const int QUESTS_PANEL_INDEX = 2;

	int currentIndex;

public slots:
	void onInventoryClicked();
	void onSkillsClicked();
	void onQuestsClicked();
};

/* -------------------- ProgressBar class ----------------- */

class ProgressBar : public QWidget
{
Q_OBJECT;
public:
	ProgressBar(QWidget *parent = 0);
	QSize sizeHint() const;

private:
	virtual double getValue() const = 0;

protected:
	QPixmap *backgroundImage;
	QPixmap *barImage;
	void paintEvent(QPaintEvent *event);
};

/* -------------------- HPBar class ----------------- */

class HPBar : public ProgressBar
{
Q_OBJECT;
public:
	HPBar(Creature *owner, QWidget *parent = 0);

private:
	Creature *owner;
	double getValue() const;
};


#endif // PANEL_H

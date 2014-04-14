#ifndef PANEL_H
#define PANEL_H

#include <QtWidgets>
#include "ImageButton.h"

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
	QPixmap backgroundImage;


};

/* ---------------------- BottomPanel class -------------- */

class BottomPanel : public Panel
{
Q_OBJECT;
public:
	BottomPanel(QWidget *parent = 0);

private:
	ImageButton *inventoryButton;
	ImageButton *skillsButton;
	ImageButton *questsButton;

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

#endif // PANEL_H

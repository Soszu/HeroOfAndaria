#include "Panels.h"
#include "System/Paths.h"
#include "System/Creature.h"
#include "System/Character.h"

/* ----------------------- Panel class ------------------ */

Panel::Panel(QWidget *parent) :
	QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize Panel::sizeHint() const
{
	return backgroundImage.size();
}

void Panel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), backgroundImage);
	QWidget::paintEvent(event);
}

/* ---------------------- BottomPanel class -------------- */

BottomPanel::BottomPanel(Character *player, QWidget *parent) :
	Panel(parent)
{
	backgroundImage.load(Data::Images::BottomPanelBackground);
	QHBoxLayout *layout = new QHBoxLayout;

	hpBar = new HPBar(player);

	inventoryButton = new ImageButton(Data::Images::InventoryButtonNormal, Data::Images::InventoryButtonDark);
	skillsButton = new ImageButton(Data::Images::SkillsButtonNormal, Data::Images::SkillsButtonDark);
	questsButton = new ImageButton(Data::Images::QuestsButtonNormal, Data::Images::QuestsButtonDark);

	connect(inventoryButton, &ImageButton::clicked, this, &BottomPanel::inventoryPressed);
	connect(skillsButton, &ImageButton::clicked, this, &BottomPanel::skillsPressed);
	connect(questsButton, &ImageButton::clicked, this, &BottomPanel::questsPressed);

	layout->addWidget(hpBar);
	layout->setAlignment(hpBar, Qt::AlignVCenter);
	layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
	for (ImageButton *btn : {inventoryButton, skillsButton, questsButton}) {
		layout->addWidget(btn);
		layout->setAlignment(btn, Qt::AlignVCenter);
	}

	layout->setAlignment(Qt::AlignVCenter);
	setLayout(layout);

	// positioning on screen
	QRect screen = QApplication::desktop()->rect();
	QSize mySize = sizeHint();
	setGeometry(30, screen.height() - mySize.height() - 30, mySize.width(), mySize.height());
}

/* -------------------- SidePanel class ----------------- */

SidePanel::SidePanel(QWidget *parent) :
	Panel(parent)
{
	backgroundImage.load(Data::Images::SidePanelBackground);

	currentIndex = INVENTORY_PANEL_INDEX;

	label = new QLabel("Inventory", this);
	QFont font = label->font();
	font.setBold(true);
	font.setPointSize(11);
	label->setFont(font);
	label->setGeometry(30, 8, backgroundImage.width() - 60, 20);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("color: black;");

	exitButton = new ImageButton(Data::Images::PanelCloseButtonNormal,
			Data::Images::PanelCloseButtonDark, "", this);
	QSize size = exitButton->sizeHint();
	exitButton->setGeometry(445, 13, size.width(), size.height());

	connect(exitButton, &ImageButton::clicked, this, &SidePanel::hide);

	// positioning on screen
	QRect screen = QApplication::desktop()->rect();
	QSize mySize = sizeHint();
	setGeometry(screen.width() - mySize.width() - 30,
			(screen.height() - mySize.height()) / 2, mySize.width(), mySize.height());
	hide();
}

void SidePanel::onInventoryClicked()
{
	if (!isHidden() && currentIndex == INVENTORY_PANEL_INDEX) {
		hide();
	} else if (isHidden()) {
		show();
	}
	//TODO set inventory panel
	currentIndex = INVENTORY_PANEL_INDEX;
	label->setText(tr("Inventory"));
}

void SidePanel::onSkillsClicked()
{
	if (!isHidden() && currentIndex == SKILLS_PANEL_INDEX) {
		hide();
	} else if (isHidden()) {
		show();
	}
	//TODO set sills panel
	currentIndex = SKILLS_PANEL_INDEX;
	label->setText(tr("Skills"));
}

void SidePanel::onQuestsClicked()
{
	if (!isHidden() && currentIndex == QUESTS_PANEL_INDEX) {
		hide();
	} else if (isHidden()) {
		show();
	}
	//TODO set quests panel
	currentIndex = QUESTS_PANEL_INDEX;
	label->setText(tr("Quests"));
}

/* -------------------- ProgressBar class ----------------- */

ProgressBar::ProgressBar(QWidget *parent):
	QWidget(parent)
{
}

QSize ProgressBar::sizeHint() const
{
	return backgroundImage.size();
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
	Q_ASSERT(backgroundImage.size() == barImage.size());
	QPainter painter(this);
	painter.drawPixmap(rect(), backgroundImage);

	double value = getValue();
	Q_ASSERT(value >= 0 && value <= 1.0);
	if (int(value * barImage.width()) > 0) {
		QPixmap copy = barImage.copy(0, 0, int(value * barImage.width()), barImage.height());
		painter.drawPixmap(copy.rect(), copy);
	}
	QWidget::paintEvent(event);
}

/* -------------------- HPBar class ----------------- */

HPBar::HPBar(Creature *owner, QWidget *parent):
	ProgressBar(parent),
	owner(owner)
{
	backgroundImage.load(Data::Images::HpBarBackground);
	barImage.load(Data::Images::HpBar);

	//TODO connect owner hitPointsChanged signal with this repaint slot, Creature is not QObject yet
}

double HPBar::getValue() const
{
	// owner->fullHitPoints() doesn't work yet, because player has no creature base
	/*
	int hp = owner->hitPoints();
	int hpMax = owner->fullHitPoints();
	Q_ASSERT(hpMax != 0);
	return double(hp) / hpMax;
	*/
	return 0.8;
}

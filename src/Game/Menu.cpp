#include "Game/Menu.h"

/* ---------------  Menu class -------------------------- */

Menu::Menu(QWidget *parent) :
	QWidget(parent),
	backgroundImage("img/menuBackground.png")
{
	stackLayout = new QStackedLayout;
	QVBoxLayout *layout = new QVBoxLayout;

	// default submenu
	defaultSubmenu = new DefaultSubmenu;
	connect(defaultSubmenu, SIGNAL(newGamePressed()), this, SLOT(setNewGameSubmenu()));
	connect(defaultSubmenu, SIGNAL(saveGamePressed()), this, SLOT(setSaveGameSubmenu()));
	connect(defaultSubmenu, SIGNAL(loadGamePressed()), this, SLOT(setLoadGameSubmenu()));
	connect(defaultSubmenu, SIGNAL(quitPressed()), this, SIGNAL(quitActivated()));
	stackLayout->addWidget(defaultSubmenu);

	// new game submenu
	newGameSubmenu = new NewGameSubmenu;
	connect(newGameSubmenu, SIGNAL(returnButtonPressed()), this, SLOT(setDefaultSubmenu()));
	connect(newGameSubmenu, SIGNAL(newGameActivated()), this, SIGNAL(newGameActivated()));
	stackLayout->addWidget(newGameSubmenu);

	// save / load game submenu
	saveGameSubmenu = new SaveGameSubmenu;
	connect(saveGameSubmenu, SIGNAL(returnButtonPressed()), this, SLOT(setDefaultSubmenu()));
	connect(saveGameSubmenu, SIGNAL(saveGameActivated()), this, SIGNAL(saveGameActivated()));
	connect(saveGameSubmenu, SIGNAL(loadGameActivated()), this, SIGNAL(loadGameActivated()));
	stackLayout->addWidget(saveGameSubmenu);

	layout->addSpacerItem(new QSpacerItem(backgroundImage.width(), backgroundImage.height()));
	layout->addLayout(stackLayout);
	setLayout(layout);
}

void Menu::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);
	painter.drawPixmap((width() - backgroundImage.width()) / 2, 10, backgroundImage);
	QWidget::paintEvent(event);
}

QString Menu::getLoadFileName() const
{
	return saveGameSubmenu->getFileName();
}

QString Menu::getSaveFileName() const
{
	return saveGameSubmenu->getFileName();
}

void Menu::setDefaultSubmenu()
{
	stackLayout->setCurrentIndex(0);
}

void Menu::setNewGameSubmenu()
{
	newGameSubmenu->clearContent();
	stackLayout->setCurrentIndex(1);
}

void Menu::setSaveGameSubmenu()
{
	saveGameSubmenu->clearContent(SaveGameSubmenu::SAVE_MENU);
	stackLayout->setCurrentIndex(2);
}

void Menu::setLoadGameSubmenu()
{
	saveGameSubmenu->clearContent(SaveGameSubmenu::LOAD_MENU);
	stackLayout->setCurrentIndex(2);
}

/* ---------------  ImageButton class -------------------------- */

ImageButton::ImageButton(QPixmap normalImage, QPixmap darkImage, QString text, QWidget *parent) :
	QPushButton(text, parent),
	normalImage_(normalImage),
	darkImage_(darkImage),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ImageButton::ImageButton(ImageButtonType type, QString text, QWidget *parent) :
	QPushButton(text, parent),
	fontPointSize_(DEFAULT_FONT_SIZE)
{
	switch (type) {
		case MENU_BUTTON:
			normalImage_.load("img/menuButtonsNormal.png");
			darkImage_.load("img/menuButtonsDark.png");
			break;
		case NEXT_ARROW_BUTTON:
			normalImage_.load("img/nextButtonNormal.png");
			darkImage_.load("img/nextButtonDark.png");
			break;
		case PREV_ARROW_BUTTON:
			normalImage_.load("img/prevButtonNormal.png");
			darkImage_.load("img/prevButtonDark.png");
			break;
		case UP_MENU_BUTTON:
			normalImage_.load("img/upButtonNormal.png");
			darkImage_.load("img/upButtonDark.png");
			break;
		case DOWN_MENU_BUTTON:
			normalImage_.load("img/downButtonNormal.png");
			darkImage_.load("img/downButtonDark.png");
			break;
	}
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ImageButton::setFontPointSize(int value)
{
	fontPointSize_ = value;
}

QSize ImageButton::sizeHint() const
{
	return QSize(normalImage_.width(), normalImage_.height());
}

void ImageButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (isDown() || !isEnabled()) {
		painter.drawPixmap(rect(), darkImage_);
	} else {
		painter.drawPixmap(rect(), normalImage_);
	}

	QFont font = QApplication::font();
	font.setPointSize(fontPointSize_);
	if (hasFocus()) {
		font.setBold(true);
	}

	QPen pen(Qt::black);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(rect(), Qt::AlignCenter, text());
}

/* ---------------  OptionsListWidget class -------------------------- */

OptionsListWidget::OptionsListWidget(QWidget *parent) :
	QWidget(parent),
	currentOption(0)
{
	QHBoxLayout *layout = new QHBoxLayout;

	prevButton = new ImageButton(ImageButton::PREV_ARROW_BUTTON);
	connect(prevButton, SIGNAL(clicked()), this, SLOT(prevOption()));
	nextButton = new ImageButton(ImageButton::NEXT_ARROW_BUTTON);
	connect(nextButton, SIGNAL(clicked()), this, SLOT(nextOption()));

	label = new QLabel();
	label->setAlignment(Qt::AlignCenter);

	layout->addWidget(prevButton);
	layout->addWidget(label);
	layout->addWidget(nextButton);
	setLayout(layout);
}

QSize OptionsListWidget::sizeHint() const
{
	return QSize(WIDTH, nextButton->height());
}

void OptionsListWidget::addOption(QString option)
{
	options.append(option);
	if (options.size() == 1) {
		label->setText(option);
	}
}

QString OptionsListWidget::getOption() const
{
	return options[currentOption];
}

void OptionsListWidget::nextOption()
{
	currentOption++;
	currentOption %= options.size();
	label->setText(options[currentOption]);
	emit optionChanged();
}

void OptionsListWidget::prevOption()
{
	currentOption += options.size() - 1;
	currentOption %= options.size();
	label->setText(options[currentOption]);
	emit optionChanged();
}

/* ---------------  MenuDialogWidget class -------------------------- */

MenuDialogWidget::MenuDialogWidget(QWidget *parent) :
	QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QHBoxLayout *buttonsLayout = new QHBoxLayout;

	layout->setAlignment(Qt::AlignCenter);
	buttonsLayout->setAlignment(Qt::AlignCenter);

	messageLabel = new QLabel;
	layout->addWidget(messageLabel);
	layout->setAlignment(messageLabel, Qt::AlignCenter);

	yesButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Yes"));
	noButton = new ImageButton(ImageButton::MENU_BUTTON, tr("No"));
	connect(yesButton, SIGNAL(clicked()), this, SIGNAL(yesPressed()));
	connect(noButton, SIGNAL(clicked()), this, SIGNAL(noPressed()));
	buttonsLayout->addWidget(noButton);
	buttonsLayout->addWidget(yesButton);
	buttonsLayout->setAlignment(yesButton, Qt::AlignCenter);
	buttonsLayout->setAlignment(noButton, Qt::AlignCenter);

	layout->addLayout(buttonsLayout);
	setLayout(layout);
}

void MenuDialogWidget::setMessage(QString message)
{
	messageLabel->setText(message);
}

/* ---------------  MenuInputWidget class -------------------------- */

MenuInputWidget::MenuInputWidget(int maxLength, QWidget *parent) :
	QLineEdit(parent),
	normalStyle("border: 3px solid #0b4270; background-color: #5491c4; color: black"),
	highlightedStyle("border: 3px solid #760000; background-color: #d96060; color: black")
{
	setStyleSheet(normalStyle);
	setAlignment(Qt::AlignCenter);
	setMaxLength(maxLength);
}

void MenuInputWidget::highlight()
{
	setStyleSheet(highlightedStyle);
}

void MenuInputWidget::unhighlight()
{
	setStyleSheet(normalStyle);
}

/* ---------------  GameSavesSlot class -------------------------- */

GameSavesSlot::GameSavesSlot(int index, QWidget *parent) :
	QLabel(parent),
	normalStyle("border: 3px solid #0b4270; background-color: #5491c4; color: black"),
	highlightedStyle("border: 3px solid #d96600; background-color: #dbd958; color: black"),
	index(index)
{
	setStyleSheet(normalStyle);
	setAlignment(Qt::AlignCenter);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize GameSavesSlot::sizeHint() const
{
	return QSize(WIDTH, HEIGHT);
}

void GameSavesSlot::highlight()
{
	setStyleSheet(highlightedStyle);
}

void GameSavesSlot::unhighlight()
{
	setStyleSheet(normalStyle);
}

void GameSavesSlot::mousePressEvent(QMouseEvent *)
{
	emit clicked(index);
}

/* ---------------  GameSavesWidget class -------------------------- */

GameSavesWidget::GameSavesWidget(int rows, QVector<QString> &saves, QWidget *parent) :
	QWidget(parent),
	visibleRows(rows),
	saves(saves),
	firstIndex(0)
{
	QVBoxLayout *layout = new QVBoxLayout();

	saveInput = new MenuInputWidget();
	connect(saveInput, SIGNAL(textChanged(QString)), this, SLOT(updateSlots()));
	connect(saveInput, SIGNAL(textChanged(QString)), saveInput, SLOT(unhighlight()));
	layout->addWidget(saveInput);
	layout->setAlignment(saveInput, Qt::AlignCenter);

	upButton = new ImageButton(ImageButton::UP_MENU_BUTTON);
	downButton = new ImageButton(ImageButton::DOWN_MENU_BUTTON);
	connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
	connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

	layout->addWidget(upButton);
	layout->setAlignment(upButton, Qt::AlignCenter);

	for (int i = 0; i < visibleRows; i++) {
		GameSavesSlot *slot = new GameSavesSlot(i);
		connect(slot, SIGNAL(clicked(int)), this, SLOT(saveSlotClicked(int)));
		savesSlots.append(slot);

		layout->addWidget(slot);
		layout->setAlignment(slot, Qt::AlignCenter);
	}
	updateSlots();

	layout->addWidget(downButton);
	layout->setAlignment(downButton, Qt::AlignCenter);

	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

void GameSavesWidget::clearContent()
{
	unhighlightInput();
	firstIndex = 0;
	saveInput->setText("");
	updateSlots();
}

QString GameSavesWidget::getSaveName() const
{
	return saveInput->text();
}

void GameSavesWidget::saveSlotClicked(int index)
{
	if (!savesSlots[index]->text().isEmpty()) {
		saveInput->setText(savesSlots[index]->text());
		updateSlots();
	}
}

void GameSavesWidget::updateSlots()
{
	for (int i = 0; i < visibleRows; i++) {
		if (firstIndex + i < saves.size()) {
			savesSlots[i]->setText(saves[firstIndex + i]);
			if (saveInput->text() == savesSlots[i]->text()) {
				savesSlots[i]->highlight();
			} else {
				savesSlots[i]->unhighlight();
			}
		} else {
			savesSlots[i]->setText("");
		}
	}
}

void GameSavesWidget::highlightInput()
{
	saveInput->highlight();
}

void GameSavesWidget::unhighlightInput()
{
	saveInput->unhighlight();
}

void GameSavesWidget::upButtonClicked()
{
	if (firstIndex > 0) {
		firstIndex--;
		updateSlots();
	}
}

void GameSavesWidget::downButtonClicked()
{
	if (firstIndex + visibleRows < saves.size()) {
		firstIndex++;
		updateSlots();
	}
}

/* ---------------  NewGameSubmenu class -------------------------- */

NewGameSubmenu::NewGameSubmenu(QWidget *parent) :
	QWidget(parent)
{
	this->setStyleSheet("QLabel {color: #94e4fc; }" );

	QVBoxLayout *layout = new QVBoxLayout;
	// name field
	QLabel *nameLabel = new QLabel(tr("Character name: "));
	nameField = new MenuInputWidget(16);

	layout->addWidget(nameLabel);
	layout->setAlignment(nameLabel, Qt::AlignCenter);

	layout->addWidget(nameField);
	connect(nameField, SIGNAL(textChanged(QString)), nameField, SLOT(unhighlight()));
	layout->setAlignment(nameField, Qt::AlignCenter);
	// race option
	QLabel *raceLabel = new QLabel(tr("Character race: "));
	raceOption = new OptionsListWidget;
	for (QString option : {tr("Human"), tr("Elf"), tr("Orc")}) {
		raceOption->addOption(option);
	}
	layout->addWidget(raceLabel);
	layout->setAlignment(raceLabel, Qt::AlignCenter);
	layout->addWidget(raceOption);
	layout->setAlignment(raceOption, Qt::AlignCenter);

	// difficulty option
	QLabel *difficultyLabel = new QLabel(tr("Game difficulty: "));
	difficultyOption = new OptionsListWidget;
	for (QString option : {tr("Easy"), tr("Medium"), tr("Hard")}) {
		difficultyOption->addOption(option);
	}
	layout->addWidget(difficultyLabel);
	layout->setAlignment(difficultyLabel, Qt::AlignCenter);
	layout->addWidget(difficultyOption);
	layout->setAlignment(difficultyOption, Qt::AlignCenter);

	startButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Start"));
	connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonPressed()));
	returnButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Retrurn"));
	connect(returnButton, SIGNAL(clicked()), this, SIGNAL(returnButtonPressed()));

	layout->addWidget(startButton);
	layout->setAlignment(startButton, Qt::AlignCenter);
	layout->addSpacerItem(new QSpacerItem(10, 60));
	layout->addWidget(returnButton);
	layout->setAlignment(returnButton, Qt::AlignCenter);

	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

void NewGameSubmenu::clearContent()
{
	nameField->clear();
	nameField->unhighlight();
}

void NewGameSubmenu::startButtonPressed()
{
	if (nameField->text().isEmpty()) {
		nameField->highlight();
	} else {
		nameField->unhighlight();
		emit newGameActivated();
	}
}

/* ---------------  SaveGameSubmenu class -------------------------- */

SaveGameSubmenu::SaveGameSubmenu(QWidget *parent) :
	QWidget(parent)
{
	this->setStyleSheet("QLabel {color: #94e4fc; }" );

	// for testing only
	for (int i = 0; i < 10; i++) {
		saves.append("save number " + QString::number(i + 1));
	}

	layout = new QStackedLayout;

	// ----------------- Main widget
	QWidget *mainWidget = new QWidget;
	QVBoxLayout *mainWidgetLayout = new QVBoxLayout;
	mainWidget->setLayout(mainWidgetLayout);

	gameSavesWidget = new GameSavesWidget(6, saves);
	mainWidgetLayout->addWidget(gameSavesWidget);
	mainWidgetLayout->setAlignment(gameSavesWidget, Qt::AlignCenter);

	saveButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Save game"));
	loadButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Load Game"));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(trySaveGame()));
	connect(loadButton, SIGNAL(clicked()), this, SLOT(tryLoadGame()));
	mainWidgetLayout->addWidget(saveButton);
	mainWidgetLayout->setAlignment(saveButton, Qt::AlignCenter);
	mainWidgetLayout->addWidget(loadButton);
	mainWidgetLayout->setAlignment(loadButton, Qt::AlignCenter);

	returnButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Return"));
	connect(returnButton, SIGNAL(clicked()), this, SIGNAL(returnButtonPressed()));
	mainWidgetLayout->addWidget(returnButton);
	mainWidgetLayout->setAlignment(returnButton, Qt::AlignCenter);

	mainWidgetLayout->setAlignment(Qt::AlignCenter);

	// -------------- Dialog widget
	dialog = new MenuDialogWidget;
	dialog->setMessage(tr("File alredy exists. Do you want to replace it?"));
	connect(dialog, SIGNAL(yesPressed()), this, SLOT(yesDialogAnswer()));
	connect(dialog, SIGNAL(noPressed()), this, SLOT(noDialogAnswer()));

	layout->addWidget(mainWidget);
	layout->addWidget(dialog);
	layout->setAlignment(Qt::AlignCenter);

	setLayout(layout);
}

QString SaveGameSubmenu::getFileName() const
{
	return gameSavesWidget->getSaveName();
}

void SaveGameSubmenu::clearContent(MenuType type)
{
	gameSavesWidget->clearContent();
	layout->setCurrentIndex(0);
	if (type == SAVE_MENU) {
		saveButton->setVisible(true);
		loadButton->setVisible(false);
	} else if (type == LOAD_MENU) {
		saveButton->setVisible(false);
		loadButton->setVisible(true);
	}
}

void SaveGameSubmenu::trySaveGame()
{
	QString name = gameSavesWidget->getSaveName();
	if (name.isEmpty()) {
		gameSavesWidget->highlightInput();
	} else {
		if (saves.contains(name)) {
			layout->setCurrentIndex(1);
		} else {
			emit saveGameActivated();
		}
	}
}

void SaveGameSubmenu::tryLoadGame()
{
	QString name = gameSavesWidget->getSaveName();
	if (!saves.contains(name)) {
		gameSavesWidget->highlightInput();
	} else {
		emit loadGameActivated();
	}
}

void SaveGameSubmenu::noDialogAnswer()
{
	layout->setCurrentIndex(0);
}

void SaveGameSubmenu::yesDialogAnswer()
{
	emit saveGameActivated();
	layout->setCurrentIndex(0);
}

/* ---------------  DefaultSubmenu class -------------------------- */

DefaultSubmenu::DefaultSubmenu(QWidget *parent) :
	QWidget(parent)
{
	continueBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Continue"));
	connect(continueBtn, SIGNAL(clicked()), this, SIGNAL(continuePressed()));
	newGameBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("New game"));
	connect(newGameBtn, SIGNAL(clicked()), this, SIGNAL(newGamePressed()));
	loadGameBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Load game"));
	connect(loadGameBtn, SIGNAL(clicked()), this, SIGNAL(loadGamePressed()));
	saveGameBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Save game"));
	connect(saveGameBtn, SIGNAL(clicked()), this, SIGNAL(saveGamePressed()));
	optionsBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Options"));
	creditsBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Credits"));
	quitBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Quit"));
	connect(quitBtn, SIGNAL(clicked()), this, SIGNAL(quitPressed()));

	QVBoxLayout *layout = new QVBoxLayout;
	for (ImageButton *btn : {continueBtn, newGameBtn, loadGameBtn,
		 saveGameBtn, optionsBtn, creditsBtn, quitBtn}) {
		layout->addWidget(btn);
		layout->setAlignment(btn, Qt::AlignCenter);
	}

	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

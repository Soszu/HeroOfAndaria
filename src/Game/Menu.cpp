#include "Game/Menu.h"
#include "System/Paths.h"

/* ---------------  Menu class -------------------------- */

Menu::Menu(QWidget *parent) :
	QWidget(parent),
	backgroundImage(Data::Images::MenuBackground)
{
	stackLayout = new QStackedLayout;
	QVBoxLayout *layout = new QVBoxLayout;

	// default submenu
	defaultSubmenu = new DefaultSubmenu;
	connect(defaultSubmenu, &DefaultSubmenu::continuePressed, this, &Menu::continueActivated);
	connect(defaultSubmenu, &DefaultSubmenu::newGamePressed,  this, &Menu::setNewGameSubmenu);
	connect(defaultSubmenu, &DefaultSubmenu::saveGamePressed, this, &Menu::setSaveGameSubmenu);
	connect(defaultSubmenu, &DefaultSubmenu::loadGamePressed, this, &Menu::setLoadGameSubmenu);
	connect(defaultSubmenu, &DefaultSubmenu::optionsPressed,  this, &Menu::setOptionsSubmenu);
	connect(defaultSubmenu, &DefaultSubmenu::quitPressed,     this, &Menu::quitActivated);
	stackLayout->addWidget(defaultSubmenu);

	// new game submenu
	newGameSubmenu = new NewGameSubmenu;
	connect(newGameSubmenu, &NewGameSubmenu::returnButtonPressed, this, &Menu::setDefaultSubmenu);
	connect(newGameSubmenu, &NewGameSubmenu::newGameActivated,    this, &Menu::newGameActivated);
	connect(newGameSubmenu, &NewGameSubmenu::newGameActivated,    this, &Menu::setDefaultSubmenu);
	stackLayout->addWidget(newGameSubmenu);

	// save / load game submenu
	saveGameSubmenu = new SaveGameSubmenu;
	connect(saveGameSubmenu, &SaveGameSubmenu::returnButtonPressed, this, &Menu::setDefaultSubmenu);
	connect(saveGameSubmenu, &SaveGameSubmenu::saveGameActivated,   this, &Menu::saveGameActivated);
	connect(saveGameSubmenu, &SaveGameSubmenu::loadGameActivated,   this, &Menu::loadGameActivated);
	stackLayout->addWidget(saveGameSubmenu);

	// options submenu
	optionsSubmenu = new OptionsSubmenu;
	connect(optionsSubmenu, &OptionsSubmenu::returnButtonPressed,    this, &Menu::setDefaultSubmenu);
	connect(optionsSubmenu, &OptionsSubmenu::controlsSubmenuPressed, this, &Menu::setControlsSubmenu);
	stackLayout->addWidget(optionsSubmenu);

	// controls submenu
	controlsSubmenu = new ControlsSubmenu;
	connect(controlsSubmenu, &ControlsSubmenu::returnButtonPressed, this, &Menu::setOptionsSubmenu);
	stackLayout->addWidget(controlsSubmenu);

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

QString Menu::loadFileName() const
{
	return saveGameSubmenu->getFileName();
}

QString Menu::saveFileName() const
{
	return saveGameSubmenu->getFileName();
}

void Menu::setDefaultSubmenu()
{
	stackLayout->setCurrentIndex(DEFAULT_SUBMENU_INDEX);
}

void Menu::setNewGameSubmenu()
{
	newGameSubmenu->clearContent();
	stackLayout->setCurrentIndex(NEW_GAME_SUBMENU_INDEX);
}

void Menu::setSaveGameSubmenu()
{
	saveGameSubmenu->clearContent(SaveGameSubmenu::SAVE_MENU);
	stackLayout->setCurrentIndex(SAVE_GAME_SUBMENU_INDEX);
}

void Menu::setLoadGameSubmenu()
{
	saveGameSubmenu->clearContent(SaveGameSubmenu::LOAD_MENU);
	stackLayout->setCurrentIndex(SAVE_GAME_SUBMENU_INDEX);
}

void Menu::setOptionsSubmenu()
{
	stackLayout->setCurrentIndex(OPTIONS_SUBMENU_INDEX);
}

void Menu::setControlsSubmenu()
{
	stackLayout->setCurrentIndex(CONTROLS_SUBMENU_INDEX);
}

/* ---------------  OptionsListWidget class -------------------------- */

OptionsListWidget::OptionsListWidget(QWidget *parent) :
	QWidget(parent),
	currentOption(0)
{
	QHBoxLayout *layout = new QHBoxLayout;

	prevButton = new ImageButton(ImageButton::PREV_ARROW_BUTTON);
	connect(prevButton, &ImageButton::clicked, this, &OptionsListWidget::prevOption);
	nextButton = new ImageButton(ImageButton::NEXT_ARROW_BUTTON);
	connect(nextButton, &ImageButton::clicked, this, &OptionsListWidget::nextOption);

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
	if (options.size() == 1)
		label->setText(option);
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
	noButton  = new ImageButton(ImageButton::MENU_BUTTON, tr("No"));
	connect(yesButton, &ImageButton::clicked, this, &MenuDialogWidget::yesPressed);
	connect(noButton,  &ImageButton::clicked, this, &MenuDialogWidget::noPressed);
	buttonsLayout->addWidget(noButton);
	buttonsLayout->addWidget(yesButton);
	buttonsLayout->setAlignment(yesButton, Qt::AlignCenter);
	buttonsLayout->setAlignment(noButton,  Qt::AlignCenter);

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
	connect(saveInput, &MenuInputWidget::textChanged, this, &GameSavesWidget::updateSlots);
	connect(saveInput, &MenuInputWidget::textChanged, saveInput, &MenuInputWidget::unhighlight);
	layout->addWidget(saveInput);
	layout->setAlignment(saveInput, Qt::AlignCenter);

	upButton = new ImageButton(ImageButton::UP_MENU_BUTTON);
	downButton = new ImageButton(ImageButton::DOWN_MENU_BUTTON);
	connect(upButton,   &ImageButton::clicked,   this, &GameSavesWidget::upButtonClicked);
	connect(downButton, &ImageButton::clicked,   this, &GameSavesWidget::downButtonClicked);

	layout->addWidget(upButton);
	layout->setAlignment(upButton, Qt::AlignCenter);

	for (int i = 0; i < visibleRows; i++) {
		GameSavesSlot *slot = new GameSavesSlot(i);
		connect(slot, &GameSavesSlot::clicked, this, &GameSavesWidget::saveSlotClicked);
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
			if (saveInput->text() == savesSlots[i]->text())
				savesSlots[i]->highlight();
			else
				savesSlots[i]->unhighlight();
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

/* ---------------  KeyChangeWidget class -------------------------- */

KeyChangeWidget::KeyChangeWidget(QString actionName, HOA::KeyFunction function, int defaultKey, QWidget *parent) :
	QWidget(parent),
	function(function),
	defaultKey(defaultKey),
	editing(false)
{
	QHBoxLayout *layout = new QHBoxLayout;

	actionNameLabel = new QLabel(actionName + ": ");
	actionNameLabel->setFixedWidth(150);
	actionNameLabel->setAlignment(Qt::AlignRight);
	layout->addWidget(actionNameLabel);
	layout->setAlignment(actionNameLabel, Qt::AlignCenter);

	keyLabel = new QLabel();
	keyLabel->setAlignment(Qt::AlignCenter);
	keyLabel->setFixedWidth(100);
	setChosenKey(defaultKey); //TODO wczytac to z Key managera po wczytaniu z pliku
	layout->addWidget(keyLabel);
	layout->setAlignment(keyLabel, Qt::AlignCenter);

	changeButton = new ImageButton(ImageButton::SMALL_MENU_BUTTON, tr("Change"));
	connect(changeButton, &ImageButton::clicked, this, &KeyChangeWidget::beginEditing);
	layout->addWidget(changeButton);
	layout->setAlignment(Qt::AlignCenter);

	layout->setAlignment(Qt::AlignVCenter);
	setLayout(layout);
}

bool KeyChangeWidget::isEditing() const
{
	return editing;
}

int KeyChangeWidget::key() const
{
	return choosenKey;
}

void KeyChangeWidget::beginEditing()
{
	setFocus();
	editing = true;
	previousKey = choosenKey;
	keyLabel->setText(tr("Press key"));
}

void KeyChangeWidget::restoreDefaultKey()
{
	setChosenKey(defaultKey);
	editing = false;
}

void KeyChangeWidget::restorePreviousKey()
{
	setChosenKey(previousKey);
	editing = false;
}

void KeyChangeWidget::setChosenKey(int key)
{
	choosenKey = key;
	keyLabel->setText(QKeySequence(key).toString());
	editing = false;
	KeyboardManager::setKeyFunction(function, key);
	emit keyChanged();
}

void KeyChangeWidget::keyPressEvent(QKeyEvent *event)
{
	if (editing)
		setChosenKey(event->key());
}

void KeyChangeWidget::focusOutEvent(QFocusEvent *event)
{
	if (editing)
		restorePreviousKey();
	QWidget::focusOutEvent(event);
}

void KeyChangeWidget::highlight()
{
	keyLabel->setStyleSheet("color: red");
}

void KeyChangeWidget::unhiglight()
{
	keyLabel->setStyleSheet("color: #94e4fc;");
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
	for (QString option : {tr("Human"), tr("Elf"), tr("Orc")})
		raceOption->addOption(option);
	layout->addWidget(raceLabel);
	layout->setAlignment(raceLabel, Qt::AlignCenter);
	layout->addWidget(raceOption);
	layout->setAlignment(raceOption, Qt::AlignCenter);

	// difficulty option
	QLabel *difficultyLabel = new QLabel(tr("Game difficulty: "));
	difficultyOption = new OptionsListWidget;
	for (QString option : {tr("Easy"), tr("Medium"), tr("Hard")})
		difficultyOption->addOption(option);
	layout->addWidget(difficultyLabel);
	layout->setAlignment(difficultyLabel, Qt::AlignCenter);
	layout->addWidget(difficultyOption);
	layout->setAlignment(difficultyOption, Qt::AlignCenter);

	startButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Start"));
	connect(startButton, &ImageButton::clicked, this, &NewGameSubmenu::startButtonPressed);
	returnButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Return"));
	connect(returnButton, &ImageButton::clicked, this, &NewGameSubmenu::returnButtonPressed);

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
	for (int i = 0; i < 10; i++)
		saves.append("save number " + QString::number(i + 1));

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
	connect(saveButton, &ImageButton::clicked, this, &SaveGameSubmenu::trySaveGame);
	connect(loadButton, &ImageButton::clicked, this, &SaveGameSubmenu::tryLoadGame);
	mainWidgetLayout->addWidget(saveButton);
	mainWidgetLayout->setAlignment(saveButton, Qt::AlignCenter);
	mainWidgetLayout->addWidget(loadButton);
	mainWidgetLayout->setAlignment(loadButton, Qt::AlignCenter);

	returnButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Return"));
	connect(returnButton, &ImageButton::clicked, this, &SaveGameSubmenu::returnButtonPressed);
	mainWidgetLayout->addWidget(returnButton);
	mainWidgetLayout->setAlignment(returnButton, Qt::AlignCenter);

	mainWidgetLayout->setAlignment(Qt::AlignCenter);

	// -------------- Dialog widget
	dialog = new MenuDialogWidget;
	dialog->setMessage(tr("File alredy exists. Do you want to replace it?"));
	connect(dialog, &MenuDialogWidget::yesPressed, this, &SaveGameSubmenu::yesDialogAnswer);
	connect(dialog, &MenuDialogWidget::noPressed,  this, &SaveGameSubmenu::noDialogAnswer);

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
		if (saves.contains(name))
			layout->setCurrentIndex(1);
		else
			emit saveGameActivated();
	}
}

void SaveGameSubmenu::tryLoadGame()
{
	QString name = gameSavesWidget->getSaveName();
	if (!saves.contains(name))
		gameSavesWidget->highlightInput();
	else
		emit loadGameActivated();
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
	connect(continueBtn, &ImageButton::clicked, this, &DefaultSubmenu::continuePressed);

	newGameBtn  = new ImageButton(ImageButton::MENU_BUTTON, tr("New game"));
	connect(newGameBtn, &ImageButton::clicked, this, &DefaultSubmenu::newGamePressed);

	loadGameBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Load game"));
	connect(loadGameBtn, &ImageButton::clicked, this, &DefaultSubmenu::loadGamePressed);

	saveGameBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Save game"));
	connect(saveGameBtn, &ImageButton::clicked, this, &DefaultSubmenu::saveGamePressed);

	optionsBtn  = new ImageButton(ImageButton::MENU_BUTTON, tr("Options"));
	connect(optionsBtn, &ImageButton::clicked, this, &DefaultSubmenu::optionsPressed);

	creditsBtn  = new ImageButton(ImageButton::MENU_BUTTON, tr("Credits"));

	quitBtn     = new ImageButton(ImageButton::MENU_BUTTON, tr("Quit"));
	connect(quitBtn, &ImageButton::clicked, this, &DefaultSubmenu::quitPressed);

	QVBoxLayout *layout = new QVBoxLayout;
	for (ImageButton *btn : {continueBtn, newGameBtn, loadGameBtn,
		saveGameBtn, optionsBtn, creditsBtn, quitBtn}) {
		layout->addWidget(btn);
		layout->setAlignment(btn, Qt::AlignCenter);
	}

	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

/* ---------------  OptionsSubmenu class -------------------------- */

OptionsSubmenu::OptionsSubmenu()
{
	QVBoxLayout *layout = new QVBoxLayout;
	graphicSubmenuBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Graphic options"));
	connect(graphicSubmenuBtn, &ImageButton::clicked, this, &OptionsSubmenu::graphicSubmenuPressed);
	soundSubmenuBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Sound options"));
	connect(soundSubmenuBtn, &ImageButton::clicked, this, &OptionsSubmenu::soundSubmenuPressed);
	controlsSubmenuBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Controls"));
	connect(controlsSubmenuBtn, &ImageButton::clicked, this, &OptionsSubmenu::controlsSubmenuPressed);
	returnBtn = new ImageButton(ImageButton::MENU_BUTTON, tr("Return"));
	connect(returnBtn, &ImageButton::clicked, this, &OptionsSubmenu::returnButtonPressed);

	for (ImageButton *button : {graphicSubmenuBtn, soundSubmenuBtn, controlsSubmenuBtn, returnBtn}) {
		layout->addWidget(button);
		layout->setAlignment(button, Qt::AlignCenter);
	}
	layout->setAlignment(Qt::AlignCenter);

	setLayout(layout);
}

/* ---------------  ControlsSubmenu class -------------------------- */

ControlsSubmenu::ControlsSubmenu(QWidget *parent) :
	QWidget(parent)
{
	this->setStyleSheet("QLabel {color: #94e4fc;}" );

	QVBoxLayout *layout = new QVBoxLayout;
	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setSpacing(0);

	collisionLabel = new QLabel();
	collisionLabel->setStyleSheet("color: red");
	collisionLabel->setAlignment(Qt::AlignCenter);
	layout->addWidget(collisionLabel);
	layout->setAlignment(collisionLabel, Qt::AlignCenter);

	addKeyChangeWidget(tr("Move forward"), HOA::KeyFunction::MoveForward, Qt::Key_W, 0, 0, gridLayout);
	addKeyChangeWidget(tr("Move backwards"), HOA::KeyFunction::MoveBackwards, Qt::Key_S, 1, 0, gridLayout);
	addKeyChangeWidget(tr("Move Left"), HOA::KeyFunction::MoveLeft, Qt::Key_A, 2, 0, gridLayout);
	addKeyChangeWidget(tr("Move Right"), HOA::KeyFunction::MoveRight, Qt::Key_D, 3, 0, gridLayout);
	addKeyChangeWidget(tr("Jump"), HOA::KeyFunction::Jump, Qt::Key_Space, 4, 0, gridLayout);

	addKeyChangeWidget(tr("Inventory"), HOA::KeyFunction::Inventory, Qt::Key_I, 0, 1, gridLayout);
	addKeyChangeWidget(tr("Skills"), HOA::KeyFunction::Skills, Qt::Key_P, 1, 1, gridLayout);
	addKeyChangeWidget(tr("Quests"), HOA::KeyFunction::Quests, Qt::Key_Q, 2, 1, gridLayout);

	setCollisionLabel();

	layout->addLayout(gridLayout);

	restoreButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Restore default"));
	restoreButton->setFontPointSize(11);
	connect(restoreButton, &ImageButton::clicked, this, &ControlsSubmenu::restoreDefault);
	layout->addWidget(restoreButton);
	layout->setAlignment(restoreButton, Qt::AlignCenter);

	returnButton = new ImageButton(ImageButton::MENU_BUTTON, tr("Return"));
	connect(returnButton, &ImageButton::clicked, this, &ControlsSubmenu::returnButtonPressed);
	layout->addWidget(returnButton);
	layout->setAlignment(returnButton, Qt::AlignCenter);

	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

void ControlsSubmenu::addKeyChangeWidget(const QString &functionName, HOA::KeyFunction function,
	int defaultKey, int row, int col, QGridLayout *layout)
{
	KeyChangeWidget *widget = new KeyChangeWidget(functionName, function, defaultKey);
	keyWidgets.append(widget);
	layout->addWidget(widget, row, col);
	connect(widget, &KeyChangeWidget::keyChanged, this, &ControlsSubmenu::setCollisionLabel);

	functionsMap[function] = widget;
}

int ControlsSubmenu::key(HOA::KeyFunction function)
{
	return functionsMap[function]->key();
}

void ControlsSubmenu::setCollisionLabel()
{
	for (KeyChangeWidget *widget : keyWidgets)
		widget->unhiglight();

	bool collision = false;
	for (int i = 0; i < (int)keyWidgets.size(); i++) {
		for (int j = i + 1; j < (int)keyWidgets.size(); j++) {
			if (keyWidgets[i]->key() == keyWidgets[j]->key()) {
				collision = true;
				keyWidgets[i]->highlight();
				keyWidgets[j]->highlight();
			}
		}
	}
	if (collision)
		collisionLabel->setText(tr("Keys collision!"));
	else
		collisionLabel->setText(" ");
}

void ControlsSubmenu::restoreDefault()
{
	for (KeyChangeWidget *widget : keyWidgets)
		widget->restoreDefaultKey();
}

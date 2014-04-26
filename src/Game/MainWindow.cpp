#include "Game/MainWindow.h"

MainWindow::MainWindow()
{
	initMenu();
	initActions();
	initPlayer();
	initGlobalMap();
	initLayout();
	initWindow();
}

MainWindow::~MainWindow()
{}

void MainWindow::initMenu()
{
	menu_ = new Menu();

	connect(menu_, &Menu::continueActivated, this, &MainWindow::onContinueActivated);
	connect(menu_, &Menu::newGameActivated,  this, &MainWindow::onNewGameActivated);
	connect(menu_, &Menu::loadGameActivated, this, &MainWindow::onLoadGameActivated);
	connect(menu_, &Menu::saveGameActivated, this, &MainWindow::onSaveGameActivated);
	connect(menu_, &Menu::quitActivated,     this, &MainWindow::onQuitActivated);
}

void MainWindow::initActions()
{
	actionQuit_ = new QAction(this);
	actionQuit_->setShortcut(tr("Ctrl+Q"));
	connect(actionQuit_, &QAction::triggered, this, &MainWindow::onQuitActivated);
	addAction(actionQuit_);

	actionContinue_ = new QAction(this);
	actionContinue_->setShortcut(tr("Ctrl+E"));
	connect(actionContinue_, &QAction::triggered, this, &MainWindow::onContinueActivated);
	addAction(actionContinue_);
}

void MainWindow::initPlayer()
{
	//TODO Soszu? save & load
	//TODO Azras load from menu if new game (in onNewGameActivated)
	player_ = new Human();
}

void MainWindow::initGlobalMap()
{
	//TODO Soszu save & load
	globalMap_ = new GlobalMap(150, 100, player_);
	graphicsGlobalMap_ = new GraphicsGlobalMap(globalMap_);

	connect(graphicsGlobalMap_, &GraphicsGlobalMap::menuActivated, this, &MainWindow::onMenuActivated);
}

void MainWindow::initLayout()
{
	stackedWidget_ = new QStackedWidget;

	stackedWidget_->insertWidget(MENU_INDEX, menu_);
	stackedWidget_->insertWidget(GLOBAL_MAP_INDEX, graphicsGlobalMap_);

	setCentralWidget(stackedWidget_);
}

void MainWindow::initWindow()
{
	onMenuActivated();
	showFullScreen();
}

void MainWindow::onContinueActivated()
{
	onGlobalMapActivated();
}

void MainWindow::onNewGameActivated()
{
	onContinueActivated();
}

void MainWindow::onLoadGameActivated()
{}

void MainWindow::onSaveGameActivated()
{}

void MainWindow::onQuitActivated()
{
	close();
}

void MainWindow::onMenuActivated()
{
	stackedWidget_->setCurrentIndex(MENU_INDEX);
}

void MainWindow::onGlobalMapActivated()
{
	stackedWidget_->setCurrentIndex(GLOBAL_MAP_INDEX);
}

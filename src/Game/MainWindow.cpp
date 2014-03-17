#include "Game/MainWindow.h"

MainWindow::MainWindow()
{
	initMenu();
	initActions();
	initGlobalMap();
	initCursor();
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
	actionQuit = new QAction(this);
	actionQuit->setShortcut(tr("Ctrl+Q"));
	connect(actionQuit, &QAction::triggered, this, &MainWindow::onQuitActivated);
	addAction(actionQuit);
}

void MainWindow::initGlobalMap()
{
	globalMap_ = new GlobalMap(2000, 1400);
	graphicsGlobalMap_ = new GraphicsGlobalMap(globalMap_);

	connect(graphicsGlobalMap_, &GraphicsGlobalMap::menuActivated, this, &MainWindow::onMenuActivated);
}

void MainWindow::initCursor()
{
	//TODO graphical pretties
	QTimer *cursorTimer = new QTimer(this);
	connect(cursorTimer, &QTimer::timeout, this, &MainWindow::updateCursor);
	cursorTimer->start(20);
}

void MainWindow::initLayout()
{
	stackedWidget_ = new QStackedWidget;

	stackedWidget_->addWidget(menu_);
	stackedWidget_->addWidget(graphicsGlobalMap_);

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

void MainWindow::updateCursor()
{
	graphicsGlobalMap_->updateCursor();
}

#include "Game/MainWindow.h"

MainWindow::MainWindow()
{
	initMenu();
	initActions();
	initGlobalMap();
	initCursor();
	initTown(); //Only for testing GraphicsTown
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
	
	// Just for graphicsTown testing
	actionTown_ = new QAction(this);
	actionTown_->setShortcut(tr("Ctrl+T"));
	connect(actionTown_, &QAction::triggered, this, &MainWindow::onShowTown);
	addAction(actionTown_);
}

void MainWindow::initGlobalMap()
{
	globalMap_ = new GlobalMap(150, 100);
	graphicsGlobalMap_ = new GraphicsGlobalMap(globalMap_);

	connect(graphicsGlobalMap_, &GraphicsGlobalMap::menuActivated, this, &MainWindow::onMenuActivated);
}

void MainWindow::initCursor()
{
	static int CURSOR_TIMEOUT = 20;

	//TODO graphical pretties
	QTimer *cursorTimer = new QTimer(this);
	connect(cursorTimer, &QTimer::timeout, this, &MainWindow::updateCursor);
	cursorTimer->start(CURSOR_TIMEOUT);
}

void MainWindow::initLayout()
{
	stackedWidget_ = new QStackedWidget;

	stackedWidget_->addWidget(menu_);
	stackedWidget_->addWidget(graphicsGlobalMap_);
	
	stackedWidget_->addWidget(graphicsTown_);
	
	setCentralWidget(stackedWidget_);
}

void MainWindow::initTown() //Only for testing GraphicsTown
{
	this->graphicsTown_ = getExample();
	connect(graphicsTown_, &GraphicsTown::leaveTown, this, &MainWindow::onHideTown);
	
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


void MainWindow::onHideTown()//Only for testing GraphicsTown
{
	stackedWidget_->setCurrentIndex(GLOBAL_MAP_INDEX);
}

void MainWindow::onShowTown()//Only for testing GraphicsTown
{
	stackedWidget_->setCurrentIndex(TOWN_INDEX);
}

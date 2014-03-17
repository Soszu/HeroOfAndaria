#include "Game/MainWindow.h"

MainWindow::MainWindow()
{
	initMenu();
	initActions();

	setCentralWidget(menu);
	showFullScreen();
}

MainWindow::~MainWindow()
{}

void MainWindow::initMenu()
{
	menu = new Menu();

	connect(menu, &Menu::continueActivated, this, &MainWindow::onContinueActivated);
	connect(menu, &Menu::newGameActivated,  this, &MainWindow::onNewGameActivated);
	connect(menu, &Menu::loadGameActivated, this, &MainWindow::onLoadGameActivated);
	connect(menu, &Menu::saveGameActivated, this, &MainWindow::onSaveGameActivated);
	connect(menu, &Menu::quitActivated,     this, &MainWindow::onQuitActivated);
}

void MainWindow::initActions()
{
	actionQuit = new QAction(this);
	actionQuit->setShortcut(tr("Ctrl+Q"));
	connect(actionQuit, &QAction::triggered, this, &MainWindow::onQuitActivated);
	addAction(actionQuit);
}

void MainWindow::onContinueActivated()
{}

void MainWindow::onNewGameActivated()
{}

void MainWindow::onLoadGameActivated()
{}

void MainWindow::onSaveGameActivated()
{}

void MainWindow::onQuitActivated()
{
	close();
}

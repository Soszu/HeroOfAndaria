#include "Game/MainWindow.h"

MainWindow::MainWindow()
{
	//TEST

	globalMap_ = new GlobalMap(1800, 1000);
	graphicsGlobalMap_ = new GraphicsGlobalMap(globalMap_);

	QWidget::showFullScreen();

	setCentralWidget(graphicsGlobalMap_);

	//except that:

	initActions();
	initCursor();
}

MainWindow::~MainWindow()
{}

void MainWindow::initActions()
{
	QAction *actionClose = new QAction(this);
	actionClose->setShortcut(tr("Ctrl+Q"));
	connect(actionClose, &QAction::triggered, this, &QMainWindow::close);
	addAction(actionClose);
}

void MainWindow::initCursor()
{
	//TODO graphical pretties
	QTimer *cursorTimer = new QTimer(this);
	connect(cursorTimer, &QTimer::timeout, this, &MainWindow::updateCursor);
	cursorTimer->start(20);
}

void MainWindow::updateCursor()
{
	QPoint localCoordinates = cursor().pos();
	globalMap_->player()->setRotation(localCoordinates);
}
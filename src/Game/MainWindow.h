#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "Game/Menu.h"
#include "Graphics/GraphicsGlobalMap.h"
#include "Graphics/GraphicsLocalMap.h"
#include "Graphics/GraphicsTown.h"

class MainWindow : public QMainWindow
{
Q_OBJECT;
public:
	MainWindow();
	~MainWindow();

private:
	Human *player_;

	GlobalMap *globalMap_;

	static const int MENU_INDEX	  = 0;
	static const int GLOBAL_MAP_INDEX = 1;

	QStackedWidget *stackedWidget_;
	Menu *menu_;
	GraphicsGlobalMap *graphicsGlobalMap_;

	QAction *actionContinue_;
	QAction *actionQuit_;

	void initActions();
	void initMenu();
	void initPlayer();
	void initGlobalMap();
	void initLayout();
	void initWindow();

private slots:
	void onContinueActivated();
	void onNewGameActivated();
	void onLoadGameActivated();
	void onSaveGameActivated();
	void onQuitActivated();

	void onMenuActivated();
	void onGlobalMapActivated();
};

#endif // MAINWINDOW_H

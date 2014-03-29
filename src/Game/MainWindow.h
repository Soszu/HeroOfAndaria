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
	GlobalMap *globalMap_;

	static const int MENU_INDEX	  = 0;
	static const int GLOBAL_MAP_INDEX = 1;

	static const int TOWN_INDEX	  = 2; //Only for testing GraphicsTown

	QStackedWidget *stackedWidget_;
	Menu *menu_;
	GraphicsGlobalMap *graphicsGlobalMap_;
	GraphicsLocalMap *graphicsLocalMap_;

	GraphicsTown *graphicsTown_; //Only for testing GraphicsTown
	QAction *actionTown_; //Only for testing GraphicsTown

	QAction *actionQuit_;

	void initActions();
	void initMenu();
	void initGlobalMap();
	void initLayout();
	void initWindow();

	void initTown(); //Only for testing GraphicsTown

private slots:
	void onContinueActivated();
	void onNewGameActivated();
	void onLoadGameActivated();
	void onSaveGameActivated();
	void onQuitActivated();

	void onMenuActivated();
	void onGlobalMapActivated();

	void onShowTown(); //Only for testing GraphicsTown
	void onHideTown(); //Only for testing GraphicsTown
};

#endif // MAINWINDOW_H

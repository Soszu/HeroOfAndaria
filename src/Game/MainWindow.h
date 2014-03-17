#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "Game/Menu.h"
#include "Graphics/GraphicsGlobalMap.h"
#include "Graphics/GraphicsLocalMap.h"

class MainWindow : public QMainWindow
{
Q_OBJECT;
public:
	MainWindow();
	~MainWindow();

private:
	Menu *menu;
	GraphicsGlobalMap *globalMap;
	GraphicsLocalMap *localMap;

	QAction *actionQuit;

	void initMenu();
	void initActions();

private slots:
	void onContinueActivated();
	void onNewGameActivated();
	void onLoadGameActivated();
	void onSaveGameActivated();
	void onQuitActivated();
};

#endif // MAINWINDOW_H


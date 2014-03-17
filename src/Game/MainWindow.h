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
	GlobalMap *globalMap_;
	Menu *menu_;
	GraphicsGlobalMap *graphicsGlobalMap_;
	GraphicsLocalMap *graphicsLocalMap_;

	void initActions();
	void initCursor();
	void updateCursor();
};

#endif // MAINWINDOW_H

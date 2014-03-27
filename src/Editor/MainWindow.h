/*
 *TODO
 * paths
 * window and widgets size in const variables listed in one place
 * separate common files if any
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "Editor/Strings.h"
#include "Editor/ContentEditor.h"
#include "Editor/CreatureEditor.h"

class MainWindow : public QMainWindow
{
Q_OBJECT;
public:
	MainWindow();
	~MainWindow();

private:
	void initMenuAndActions();
	void initContentEditors();
	void initModelsList();
	void initEditorsWidgets();
	void initLayout();

	bool loadContent(const QString &path);
	bool saveContent(const QString &path);
	int checkForUnsavedChanges();

	QString openedFilePath;

	QAction *menuFileSave;
	QAction *menuFileSaveAs;

	QSplitter *placeholder;
	QListWidget *modelsList_;
	QStackedWidget *modelsWidgets_;
	QList<ContentEditor *> contentEditors_;

private slots:
	void onNewActivated();
	void onLoadActivated();
	void onSaveActivated();
	void onSaveAsActivated();
	void onQuitActivated();

	void startEditing();

signals:
	void modelSaved();
};

#endif // MAINWINDOW_H

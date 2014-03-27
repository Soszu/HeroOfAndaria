#include "Editor/MainWindow.h"

MainWindow::MainWindow()
{
	resize(800, 600);

	initMenuAndActions();
	initContentEditors();
	initModelsList();
	initEditorsWidgets();
	initLayout();
}

MainWindow::~MainWindow()
{
	qDeleteAll(contentEditors_);
}

void MainWindow::initMenuAndActions()
{
	QMenu *fileMenu = menuBar()->addMenu(HOAEditor::Strings::MenuFile);

	QAction *menuFileNew    = new QAction(HOAEditor::Strings::MenuFileNew, this);
	QAction *menuFileLoad   = new QAction(HOAEditor::Strings::MenuFileLoad, this);
	menuFileSave            = new QAction(HOAEditor::Strings::MenuFileSave, this);
	menuFileSaveAs          = new QAction(HOAEditor::Strings::MenuFileSaveAs, this);
	QAction *menuFileQuit   = new QAction(HOAEditor::Strings::MenuFileQuit, this);

	connect(menuFileNew, &QAction::triggered, this, &MainWindow::onNewActivated);
	connect(menuFileLoad, &QAction::triggered, this, &MainWindow::onLoadActivated);
	connect(menuFileSave, &QAction::triggered, this, &MainWindow::onSaveActivated);
	connect(menuFileSaveAs, &QAction::triggered, this, &MainWindow::onSaveAsActivated);
	connect(menuFileQuit, &QAction::triggered, this, &MainWindow::onQuitActivated);

	menuFileNew->setShortcut(HOAEditor::Shortcuts::MenuFileNew);
	menuFileLoad->setShortcut(HOAEditor::Shortcuts::MenuFileLoad);
	menuFileSave->setShortcut(HOAEditor::Shortcuts::MenuFileSave);
	menuFileQuit->setShortcut(HOAEditor::Shortcuts::MenuFileQuit);

	menuFileSave->setEnabled(false);
	menuFileSaveAs->setEnabled(false);

	fileMenu->addAction(menuFileNew);
	fileMenu->addAction(menuFileLoad);
	fileMenu->addAction(menuFileSave);
	fileMenu->addAction(menuFileSaveAs);
	fileMenu->addSeparator();
	fileMenu->addAction(menuFileQuit);
}

void MainWindow::initContentEditors()
{
	contentEditors_.push_back(new CreatureEditor());
	for (ContentEditor *editor : contentEditors_)
		connect(this, &MainWindow::modelSaved, editor, &ContentEditor::modelSaved);
}

void MainWindow::initModelsList()
{
	modelsList_ = new QListWidget();
	for (ContentEditor *editor : contentEditors_)
		modelsList_->addItem(editor->name());
}

void MainWindow::initEditorsWidgets()
{
	modelsWidgets_ = new QStackedWidget();
	for (ContentEditor *editor : contentEditors_)
		modelsWidgets_->addWidget(editor->widget());

	connect (modelsList_, &QListWidget::currentRowChanged, modelsWidgets_, &QStackedWidget::setCurrentIndex);
}

void MainWindow::initLayout()
{
	placeholder = new QSplitter(this);
	placeholder->addWidget(modelsList_);
	placeholder->addWidget(modelsWidgets_);

	setCentralWidget(placeholder);

	modelsList_->setMaximumWidth(100);

	placeholder->setVisible(false);

	statusBar()->showMessage(HOAEditor::Messages::HowToStart);
}

void MainWindow::startEditing()
{
	menuFileSave->setEnabled(true);
	menuFileSaveAs->setEnabled(true);

	placeholder->setVisible(true);
}

bool MainWindow::loadContent(const QString &path)
{
	if (path.isEmpty())
		return false;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QDataStream in(&file);

	for (ContentEditor * editor : contentEditors_)
		editor->loadFromStream(in);

	file.close();
	statusBar()->showMessage(HOAEditor::Messages::ContentLoaded);
	return true;
}

bool MainWindow::saveContent(const QString &path)
{
	if (path.isEmpty())
		return false;

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	QDataStream out(&file);

	for (ContentEditor * editor : contentEditors_)
		editor->saveToStream(out);

	file.close();
	statusBar()->showMessage(HOAEditor::Messages::ContentSaved);
	return true;
}

int MainWindow::checkForUnsavedChanges()
{
	bool unsavedChanges = false;
	for (ContentEditor *editor : contentEditors_)
		if (editor->isChanged()){
			unsavedChanges = true;
			break;
		}
		if (!unsavedChanges)
			return QMessageBox::Discard;

		QMessageBox msgBox;
	msgBox.setText("Content has been modified.");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);

	return msgBox.exec();
}

void MainWindow::onNewActivated()
{
	startEditing();

	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			onSaveActivated();
			return;
		case QMessageBox::Discard:

			for (ContentEditor *editor : contentEditors_)
				editor->clear();
			return;
		default :
			return;
	}
}

void MainWindow::onLoadActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			onSaveActivated();
			return;
		case QMessageBox::Discard:
			break;
		default :
			return;
	}

	QString path = QFileDialog::getOpenFileName(this, HOAEditor::Strings::LoadFileDialog, QString(), HOAEditor::Strings::HOAContentFiles);
	if (loadContent(path))
		startEditing();
}

void MainWindow::onSaveActivated()
{
	if (openedFilePath.isEmpty())
		onSaveAsActivated();

	if (saveContent(openedFilePath))
		emit modelSaved();
}

void MainWindow::onSaveAsActivated()
{
	QString path = QFileDialog::getSaveFileName(this, HOAEditor::Strings::SaveFileDialog, QString(), HOAEditor::Strings::HOAContentFiles);

	if (saveContent(path)){
		emit modelSaved();
		openedFilePath = path;
	}
}

void MainWindow::onQuitActivated()
{
	close();
}

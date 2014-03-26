#ifndef MENU_H
#define MENU_H

#include <QtWidgets>
#include "Graphics/KeyboardManager.h"

class NewGameSubmenu;
class SaveGameSubmenu;
class DefaultSubmenu;
class OptionsSubmenu;
class ControlsSubmenu;

/* ---------------  Menu class -------------------------- */

class Menu : public QWidget
{
Q_OBJECT;
public:
	Menu(QWidget *parent = nullptr);

	QString saveFileName() const;
	QString loadFileName() const;
	int controlKey(HOA::KeyFunction function) const;

private:
	static const int DEFAULT_SUBMENU_INDEX   = 0;
	static const int NEW_GAME_SUBMENU_INDEX	 = 1;
	static const int SAVE_GAME_SUBMENU_INDEX = 2;
	static const int OPTIONS_SUBMENU_INDEX   = 3;
	static const int CONTROLS_SUBMENU_INDEX  = 4;

	QStackedLayout *stackLayout;
	DefaultSubmenu *defaultSubmenu;
	NewGameSubmenu *newGameSubmenu;
	SaveGameSubmenu *saveGameSubmenu;
	OptionsSubmenu *optionsSubmenu;
	ControlsSubmenu *controlsSubmenu;

	QPixmap backgroundImage;

protected:
	void paintEvent(QPaintEvent *event);

signals:
	void continueActivated();
	void newGameActivated();
	void loadGameActivated();
	void saveGameActivated();
	void quitActivated();
	void controlsChanged();

public slots:
	void setDefaultSubmenu();
	void setNewGameSubmenu();
	void setSaveGameSubmenu();
	void setLoadGameSubmenu();
	void setOptionsSubmenu();
	void setControlsSubmenu();
};

/* ---------------  ImageButton class -------------------------- */

class ImageButton : public QPushButton
{
Q_OBJECT;
public:
	enum ImageButtonType : quint8 {
		MENU_BUTTON,
		SMALL_MENU_BUTTON,
		NEXT_ARROW_BUTTON,
		PREV_ARROW_BUTTON,
		UP_MENU_BUTTON,
		DOWN_MENU_BUTTON
	};

	ImageButton(QPixmap normalImage, QPixmap darkImage, QString text = "", QWidget *parent = 0);
	ImageButton(ImageButtonType type, QString text = "", QWidget *parent = 0);
	void setFontPointSize(int value);
	QSize sizeHint() const;

private:
	QPixmap normalImage_;
	QPixmap darkImage_;
	int fontPointSize_;
	static const int DEFAULT_FONT_SIZE = 11;

protected:
	void paintEvent(QPaintEvent *);

};

/* ---------------  OptionsListWidget class -------------------------- */

class OptionsListWidget : public QWidget
{
Q_OBJECT;
public:
	OptionsListWidget(QWidget *parent = 0);

	void addOption(QString option);
	QString getOption() const;

	QSize sizeHint() const;

private:
	static const int WIDTH = 200;

	ImageButton *prevButton;
	ImageButton *nextButton;
	QLabel *label;
	QVector <QString> options;

	int currentOption;

signals:
	void optionChanged();

public slots:
	void prevOption();
	void nextOption();
};

/* ---------------  MenuDialogWidget class -------------------------- */

class MenuDialogWidget : public QWidget
{
Q_OBJECT;
public:
	MenuDialogWidget(QWidget *parent = 0);

	void setMessage(QString message);

private:
	QLabel *messageLabel;
	ImageButton *yesButton;
	ImageButton *noButton;

signals:
	void yesPressed();
	void noPressed();
};

/* ---------------  MenuInputWidget class -------------------------- */

class MenuInputWidget : public QLineEdit
{
Q_OBJECT;
public:
	MenuInputWidget(int maxLength = 16, QWidget *parent = 0);

private:
	const QString normalStyle;
	const QString highlightedStyle;

public slots:
	void highlight();
	void unhighlight();
};

/* ---------------  GameSavesSlot class -------------------------- */

class GameSavesSlot : public QLabel
{
Q_OBJECT;
public:
	GameSavesSlot(int index, QWidget *parent = 0);
	QSize sizeHint() const;

private:
	static const int WIDTH = 300;
	static const int HEIGHT = 28;
	QString normalStyle;
	QString highlightedStyle;
	// which slot it is in GameSavesWidget
	int index;

protected:
	void mousePressEvent(QMouseEvent *);

signals:
	void clicked(int index);

public slots:
	void highlight();
	void unhighlight();

};

/* ---------------  GameSavesWidget class -------------------------- */

class GameSavesWidget : public QWidget
{
Q_OBJECT;
public:
	GameSavesWidget(int rows, QVector<QString> &saves, QWidget *parent = 0);
	void clearContent();
	QString getSaveName() const;

private:
	const int visibleRows;
	const QVector<QString> &saves;
	MenuInputWidget *saveInput;

	ImageButton *upButton;
	ImageButton *downButton;
	QVector<GameSavesSlot * > savesSlots;

	// which save is in the first GameSavesSlot widget
	int firstIndex;

public slots:
	// updates informations about saves in each slot
	void updateSlots();

	void saveSlotClicked(int index);
	void downButtonClicked();
	void upButtonClicked();
	void highlightInput();
	void unhighlightInput();

};

/* ---------------  KeyChange class -------------------------- */

class KeyChangeWidget : public QWidget
{
Q_OBJECT;
public:
	KeyChangeWidget(QString actionName, int defaultKey, QWidget *parent = 0);

	int key() const;
	bool isEditing() const;

private:
	int choosenKey;
	int defaultKey;
	bool editing;
	// key before clicking change button
	int previousKey;

	QLabel *actionNameLabel;
	QLabel *keyLabel;
	ImageButton *changeButton;

	void setChosenKey(int key);

protected:
	void keyPressEvent(QKeyEvent *event);
	void focusOutEvent(QFocusEvent *event);

signals:
	void keyChanged(int newKey);

public slots:
	void beginEditing();
	void restoreDefaultKey();
	void restorePreviousKey();

	void highlight();
	void unhiglight();

};

/* ---------------  NewGameSubmenu class -------------------------- */

class NewGameSubmenu : public QWidget
{
Q_OBJECT;
public:
	NewGameSubmenu(QWidget *parent = 0);
	void clearContent();

private:
	MenuInputWidget *nameField;
	OptionsListWidget *raceOption;
	OptionsListWidget *difficultyOption;
	ImageButton *startButton;
	ImageButton *returnButton;

signals:
	void returnButtonPressed();
	void newGameActivated();

public slots:
	void startButtonPressed();
};

/* ---------------  SaveGameSubmenu class -------------------------- */

class SaveGameSubmenu : public QWidget
{
Q_OBJECT;
public:
	enum MenuType : quint8 {
		SAVE_MENU,
		LOAD_MENU
	};

	SaveGameSubmenu(QWidget *parent = 0);

	void clearContent(MenuType type);

	QString getFileName() const;

private:
	QStackedLayout *layout;

	GameSavesWidget *gameSavesWidget;
	ImageButton *saveButton;
	ImageButton *loadButton;
	ImageButton *returnButton;

	MenuDialogWidget *dialog;

	QVector<QString> saves;

signals:
	void returnButtonPressed();
	void saveGameActivated();
	void loadGameActivated();

public slots:
	void trySaveGame();
	void tryLoadGame();
	void noDialogAnswer();
	void yesDialogAnswer();
};

/* ---------------  DefaultSubmenu class --------------------------- */

class DefaultSubmenu : public QWidget
{
Q_OBJECT;
public:
	DefaultSubmenu(QWidget *parent = 0);

private:
	ImageButton *continueBtn;
	ImageButton *newGameBtn;
	ImageButton *loadGameBtn;
	ImageButton *saveGameBtn;
	ImageButton *optionsBtn;
	ImageButton *creditsBtn;
	ImageButton *quitBtn;

signals:
	void continuePressed();
	void newGamePressed();
	void saveGamePressed();
	void loadGamePressed();
	void optionsPressed();
	void quitPressed();
};

/* ---------------  OptionsSubmenu class --------------------------- */

class OptionsSubmenu : public QWidget
{
Q_OBJECT;
public:
	OptionsSubmenu();

private:
	ImageButton *graphicSubmenuBtn;
	ImageButton *soundSubmenuBtn;
	ImageButton *controlsSubmenuBtn;
	ImageButton *returnBtn;

signals:
	void graphicSubmenuPressed();
	void soundSubmenuPressed();
	void controlsSubmenuPressed();
	void returnButtonPressed();

};

/* ---------------  ControlsSubmenu class --------------------------- */

class ControlsSubmenu : public QWidget
{
Q_OBJECT;

public:
	ControlsSubmenu(QWidget *parent = 0);
	bool isEditing();
	int key(HOA::KeyFunction function);

private:
	QLabel *collisionLabel;
	QVector <KeyChangeWidget *> keyWidgets;
	ImageButton *restoreButton;
	ImageButton *returnButton;
	QMap <HOA::KeyFunction, KeyChangeWidget *> functionsMap;

	void addKeyChangeWidget(const QString &functionName, HOA::KeyFunction function,
		int defaultKey, int row, int col, QGridLayout *layout);

signals:
	void controlsChanged();
	void returnButtonPressed();

public slots:
	void setCollisionLabel();
	void restoreDefault();

};

#endif // MENU_H

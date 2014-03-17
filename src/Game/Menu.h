#ifndef MENU_H
#define MENU_H

#include <QtWidgets>

class NewGameSubmenu;
class SaveGameSubmenu;
class DefaultSubmenu;

/* ---------------  Menu class -------------------------- */

class Menu : public QWidget
{
Q_OBJECT;
public:
	Menu(QWidget *parent = 0);

	QString getSaveFileName() const;
	QString getLoadFileName() const;

private:
	QStackedLayout *stackLayout;
	DefaultSubmenu *defaultSubmenu;
	NewGameSubmenu *newGameSubmenu;
	SaveGameSubmenu *saveGameSubmenu;

	QPixmap backgroundImage;

protected:
	void paintEvent(QPaintEvent *event);

signals:
	void continueActivated();
	void newGameActivated();
	void loadGameActivated();
	void saveGameActivated();
	void quitActivated();

public slots:
	void setDefaultSubmenu();
	void setNewGameSubmenu();
	void setSaveGameSubmenu();
	void setLoadGameSubmenu();
};

/* ---------------  ImageButton class -------------------------- */

class ImageButton : public QPushButton
{
Q_OBJECT;
public:
	enum ImageButtonType : quint8 {
		MENU_BUTTON,
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
	static const int DEFAULT_FONT_SIZE = 12;

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
	void quitPressed();
};

/* ---------------  Data::Images namespace ------------------------- */

namespace Data {
	namespace Images {
		const QString Preffix           = "img";
		const QString MenuBackground    = Preffix + "/menuBackground.png";
		const QString MenuButtonsNormal = Preffix + "/menuButtonsNormal.png";
		const QString MenuButtonsDark   = Preffix + "/menuButtonsDark.png";
		const QString NextButtonNormal  = Preffix + "/nextButtonNormal.png";
		const QString NextButtonDark    = Preffix + "/nextButtonDark.png";
		const QString PrevButtonNormal  = Preffix + "/prevButtonNormal.png";
		const QString PrevButtonDark    = Preffix + "/prevButtonDark.png";
		const QString UpButtonNormal    = Preffix + "/upButtonNormal.png";
		const QString UpButtonDark      = Preffix + "/upButtonDark.png";
		const QString DownButtonNormal  = Preffix + "/downButtonNormal.png";
		const QString DownButtonDark    = Preffix + "/downButtonDark.png";
	}
}

#endif // MENU_H

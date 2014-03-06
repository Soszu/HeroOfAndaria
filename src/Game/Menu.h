#ifndef MENU_H
#define MENU_H

#include <QtWidgets>

class Menu : public QWidget
{
public:
	Menu();
	
signals:
	void continueActivated();
	void newGameActivated();
	void saveGameActivated();
	//...//
	
private:
	/**
	 * Continue
	 * New Game
	 * Save Game
	 * Load Game
	 * Options
	 * Credits
	 * Quit
	 */
	
	/** Options
	 */
};

#endif // MENU_H

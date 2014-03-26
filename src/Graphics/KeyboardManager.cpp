#include "KeyboardManager.h"

//QHash <int, HOA::KeyFunction> KeyboardManager::keyFunctions_;

KeyboardManager & KeyboardManager::getInstance()
{
	static KeyboardManager keyboardManager;
	return keyboardManager;
}

void KeyboardManager::setKeyFunction(HOA::KeyFunction keyFunction, int key)
{
	// removing previous entry
	KeyboardManager::getInstance().keyFunctions_.remove(
		KeyboardManager::getInstance().keyFunctions_.key(keyFunction));
	KeyboardManager::getInstance().keyFunctions_[key] = keyFunction;

	//TODO save to file
}

HOA::KeyFunction KeyboardManager::keyFunction(int key)
{
	return getInstance().keyFunctions_[key];
}

bool KeyboardManager::hasKeyFunction(int key)
{
	return getInstance().keyFunctions_.contains(key);
}

KeyboardManager::KeyboardManager()
{
	//TODO load from file

	keyFunctions_[Qt::Key_Escape] = HOA::KeyFunction::Menu;
}


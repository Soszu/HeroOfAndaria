#include "KeyboardManager.h"

//QHash <int, HOA::KeyFunction> KeyboardManager::keyFunctions_;

KeyboardManager & KeyboardManager::getInstance()
{
	static KeyboardManager keyboardManager;
	return keyboardManager;
}

void KeyboardManager::setKeyFunction(HOA::KeyFunction keyFunction, int key)
{
	getInstance().keyFunctions_[key] = keyFunction;
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
	//TODO write from && to settings

	keyFunctions_[Qt::Key_W] = HOA::KeyFunction::MoveForward;
	keyFunctions_[Qt::Key_S] = HOA::KeyFunction::MoveBackwards;
	keyFunctions_[Qt::Key_A] = HOA::KeyFunction::MoveLeft;
	keyFunctions_[Qt::Key_D] = HOA::KeyFunction::MoveRight;

	keyFunctions_[Qt::Key_Escape] = HOA::KeyFunction::Menu;
}


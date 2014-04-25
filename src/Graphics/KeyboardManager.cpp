#include "KeyboardManager.h"

//QHash <int, HOA::KeyFunction> KeyboardManager::keyFunctions_;

KeyboardManager & KeyboardManager::instance()
{
	static KeyboardManager keyboardManager;
	return keyboardManager;
}

void KeyboardManager::setKeyFunction(HOA::KeyFunction keyFunction, int key)
{
	// removing previous entry
	KeyboardManager::instance().keyFunctions_.remove(
		KeyboardManager::instance().keyFunctions_.key(keyFunction));
	KeyboardManager::instance().keyFunctions_[key] = keyFunction;

	//TODO save to file
}

HOA::KeyFunction KeyboardManager::keyFunction(int key)
{
	return instance().keyFunctions_[key];
}

bool KeyboardManager::hasKeyFunction(int key)
{
	return instance().keyFunctions_.contains(key);
}

int KeyboardManager::primaryKey(HOA::KeyFunction keyFunction)
{
	return instance().keyFunctions_.key(keyFunction);
}

KeyboardManager::KeyboardManager()
{
	//TODO load from file

	keyFunctions_[Qt::Key_Escape] = HOA::KeyFunction::Menu;

	//TODO specialized settings for different windows

	keyFunctions_[Qt::Key_Return] = HOA::KeyFunction::EnterLocation;

	keyFunctions_[Qt::Key_Down]  = HOA::KeyFunction::CameraDown;
	keyFunctions_[Qt::Key_Up]    = HOA::KeyFunction::CameraUp;
	keyFunctions_[Qt::Key_Left]  = HOA::KeyFunction::CameraLeft;
	keyFunctions_[Qt::Key_Right] = HOA::KeyFunction::CameraRight;

	keyFunctions_[Qt::Key_H] = HOA::KeyFunction::TriggerHealthVisibility;
	keyFunctions_[Qt::Key_U] = HOA::KeyFunction::TriggerBoundingBoxesVisibility;
}


#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <QtWidgets>

namespace HOA {
	enum class KeyFunction : quint8 {
		None,

		MoveForward,
		MoveBackwards,
		MoveLeft,
		MoveRight,
		Jump,

		EnterLocation,

		Inventory,
		Skills,
		Quests,
		Menu,
	};
}

class KeyboardManager
{
public:
	static KeyboardManager & instance();

	//TODO scopes: localmap, globalmap
	static void setKeyFunction(HOA::KeyFunction keyFunction, int key);
	static HOA::KeyFunction keyFunction(int key);
	static bool hasKeyFunction(int key);

	static int primaryKey(HOA::KeyFunction keyFunction);

private:
	QHash <int, HOA::KeyFunction> keyFunctions_;

	KeyboardManager();
	KeyboardManager(const KeyboardManager &) = delete;
};

#endif // KEYBOARD_MANAGER_H

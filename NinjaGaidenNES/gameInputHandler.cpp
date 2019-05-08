#include "gameInputHandler.h"
#include "helperFunction.h"
#include "MainCharacter.h"
#include "GameWorld.h"

void GameKeyHandler::onKeyState(bool keyStates[])
{
	// Your Handling
	MainCharacter::getInstance()->handleKeyInput(keyStates);
}

void GameKeyHandler::onKeyPress(int keycode)
{
	// Your Handling

	showBug((wchar_t*)L"Key %d pressed\n", keycode);
}

void GameKeyHandler::onKeyRelease(int keycode)
{
	// Your Handling

	
}

void GameMouseHandler::onMouseState(DIMOUSESTATE * mouseStates)
{
	// Your Handling

	if (mouseStates->lX | mouseStates->lY != 0)
		showBug((wchar_t*)L"[INFO]: Mouse deltaMove (%d;%d)\n", mouseStates->lX, mouseStates->lY);
}

void GameMouseHandler::onMouseButtonPress(int button)
{
	// Your Handling

	showBug((wchar_t*)L"[INFO]: Mouse button %d pressed\n", button);
}

void GameMouseHandler::onMouseButtonRelease(int button)
{
	// Your Handling

}

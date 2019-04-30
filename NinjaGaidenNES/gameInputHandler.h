#pragma once

class GameKeyHandler;
typedef class GameKeyHandler * LPGAMEKH;
class GameMouseHandler;
typedef class GameMouseHandler * LPGAMEMH;

#include "DxMouse.h"
#include "DxKeyboard.h"

class GameKeyHandler : public KeyEventHandler
{
	void onKeyState(bool keyStates[]);
	void onKeyPress(int keycode);
	void onKeyRelease(int keycode);
};

class GameMouseHandler : public MouseEventHandler
{
	void onMouseState(DIMOUSESTATE * mouseStates);
	void onMouseButtonPress(int button);
	void onMouseButtonRelease(int button);
};
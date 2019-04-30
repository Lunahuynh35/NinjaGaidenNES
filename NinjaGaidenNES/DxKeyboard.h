#pragma once

#define KEYBOARD_BUFFER_SIZE 1024

class DxKeyboard;
typedef class DxKeyboard * LPDXKEYB;
class KeyEventHandler;
typedef class KeyEventHandler * LPKEYEVENTHANDLER;

#include <dinput.h>

class DxKeyboard
{
private:
	LPDIRECTINPUTDEVICE8 directInputKeyboard;
	LPKEYEVENTHANDLER keyboardHandler;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	void collectState();
	void collectAllKeysPressedInBuffer();

public:
	DxKeyboard();
	~DxKeyboard();
	bool initialize(LPKEYEVENTHANDLER keyboardHandler, LPDIRECTINPUT8 directInput);
	void process();
};

class KeyEventHandler
{
public:
	virtual void onKeyState(bool keyStates[]) = 0;
	virtual void onKeyPress(int keycode) = 0;
	virtual void onKeyRelease(int keycode) = 0;
};
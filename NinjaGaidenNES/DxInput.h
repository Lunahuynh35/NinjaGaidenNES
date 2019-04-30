#pragma once

#define DIRECTINPUT_VER 0x0800

class DxInput;
typedef class DxInput * LPDXINPUT;
class DxMouse;
typedef class DxMouse * LPDXMOUSE;
class MouseEventHandler;
typedef class MouseEventHandler * LPMOUSEEVENTHANDLER;
class DxKeyboard;
typedef class DxKeyboard * LPDXKEYB;
class KeyEventHandler;
typedef class KeyEventHandler * LPKEYEVENTHANDLER;

#include <d3d9.h>
#include <dinput.h>

class DxInput
{
private:
	static LPDXINPUT instance;
	LPDIRECTINPUT8 directInput;
	LPDXMOUSE directMouse;
	LPDXKEYB directKeyboard;

	DxInput();
	bool initializeDirectInput();
	
public:
	~DxInput();
	static LPDXINPUT getInstance();
	bool initialize(LPKEYEVENTHANDLER keyHandler, LPMOUSEEVENTHANDLER mouseHandler);
	void processInput();
};
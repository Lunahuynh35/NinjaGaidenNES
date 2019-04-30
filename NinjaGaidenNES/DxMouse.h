#pragma once

class DxMouse;
typedef class DxMouse * LPDXMOUSE;
class MouseEventHandler;
typedef class MouseEventHandler * LPMOUSEEVENTHANDLER;

#include <dinput.h>

class DxMouse
{
private:
	LPDIRECTINPUTDEVICE8 directInputMouse;
	LPMOUSEEVENTHANDLER mouseHandler;
	DIMOUSESTATE mouseStates;

	void collectState();

public:
	DxMouse();
	~DxMouse();
	bool initialize(LPMOUSEEVENTHANDLER mouseHandler, LPDIRECTINPUT8 directInput);
	void process();
};

class MouseEventHandler
{
public:
	virtual void onMouseState(DIMOUSESTATE * mouseStates) = 0;
	virtual void onMouseButtonPress(int button) = 0;
	virtual void onMouseButtonRelease(int button) = 0;
};
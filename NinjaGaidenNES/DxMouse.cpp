#include "helperFunction.h"
#include "DxGraph.h"
#include "DxMouse.h"

DxMouse::DxMouse()
{
	directInputMouse = NULL;
	mouseHandler = NULL;
}

DxMouse::~DxMouse()
{
	if (directInputMouse != NULL)
	{
		directInputMouse->Unacquire();
		directInputMouse->Release();
		directInputMouse = NULL;
	}
}

bool DxMouse::initialize(LPMOUSEEVENTHANDLER mouseHandler, LPDIRECTINPUT8 directInput)
{
	HWND hWnd = DxGraph::getInstance()->getWindowHandler();
	HRESULT result = directInput->CreateDevice(GUID_SysMouse, &directInputMouse, NULL);
	if (result != DI_OK)
	{
		showBug((wchar_t*)L"[ERROR]: Create Directinput Mouse unsuccesfull\n");
		return false;
	}
	result = directInputMouse->SetDataFormat(&c_dfDIMouse);
	result = directInputMouse->SetCooperativeLevel(
		hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
	);
	result = directInputMouse->Acquire();

	this->mouseHandler = mouseHandler;
	return true;
}

void DxMouse::collectState()
{
	HRESULT result = directInputMouse->GetDeviceState(sizeof(mouseStates), (LPVOID)&mouseStates);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			HRESULT h = directInputMouse->Acquire();
			if (FAILED(h))
				showBug((wchar_t*)L"[WARNING]: Mouse didn't acquire\n");
		}
		else
			showBug((wchar_t*)L"[WARNING]: Can't get mouse state\n");
	}
}

void DxMouse::process()
{
	collectState();

	mouseHandler->onMouseState(&mouseStates);

	for (int i = 0; i < 4; i++)
	{
		if ((mouseStates.rgbButtons[i] & 0x80) > 0)
			mouseHandler->onMouseButtonPress(i);
		else
			mouseHandler->onMouseButtonRelease(i);
	}
}
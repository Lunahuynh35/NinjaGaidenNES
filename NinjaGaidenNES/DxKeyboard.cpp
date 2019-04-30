#include "helperFunction.h"
#include "DxKeyboard.h"
#include "DxGraph.h"

DxKeyboard::DxKeyboard()
{
	directInputKeyboard = NULL;
	keyboardHandler = NULL;
}

DxKeyboard::~DxKeyboard()
{
	if (directInputKeyboard != NULL)
	{
		directInputKeyboard->Unacquire();
		directInputKeyboard->Release();
		directInputKeyboard = NULL;
	}
}

bool DxKeyboard::initialize(LPKEYEVENTHANDLER keyboardHandler, LPDIRECTINPUT8 directInput)
{
	HWND hWnd = DxGraph::getInstance()->getWindowHandler();
	HRESULT result = directInput->CreateDevice(GUID_SysKeyboard, &directInputKeyboard, NULL);
	if (result != DI_OK)
	{
		showBug((wchar_t*)L"[ERROR]: Create Directinput Keyboard unsuccesfull\n");
		return false;
	}
	result = directInputKeyboard->SetDataFormat(&c_dfDIKeyboard);
	result = directInputKeyboard->SetCooperativeLevel(
		hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
	);

	DIPROPDWORD deviceDataBuffer = createDeviceDataBuffer(KEYBOARD_BUFFER_SIZE);
	result = directInputKeyboard->SetProperty(DIPROP_BUFFERSIZE, &deviceDataBuffer.diph);
	if (result != DI_OK)
	{
		showBug((wchar_t*)L"[ERROR]: Create buffered data unsuccesfull\n");
		return false;
	}

	result = directInputKeyboard->Acquire();
	this->keyboardHandler = keyboardHandler;
	return true;
}

void DxKeyboard::collectState()
{
	HRESULT result = directInputKeyboard->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			HRESULT h = directInputKeyboard->Acquire();
			if (FAILED(h))
				showBug((wchar_t*)L"[WARNING]: Keyboard didn't acquire\n");
		}
		else
			showBug((wchar_t*)L"[WARNING]: Can't get keyboard state\n");
	}
}

void DxKeyboard::collectAllKeysPressedInBuffer()
{
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT result = directInputKeyboard->GetDeviceData(
		sizeof(DIDEVICEOBJECTDATA),
		keyEvents,
		&dwElements,
		0
	);
	if (FAILED(result))
		showBug((wchar_t*)L"[WARNING]: Can't get key pressed in buffer\n");
}

void DxKeyboard::process()
{
	collectState();
	bool keystates[256];
	for (int i = 0; i < 256; i++)
		keystates[i] = (keyStates[i] & 0x80) > 0;
	keyboardHandler->onKeyState(keystates);

	collectAllKeysPressedInBuffer();

	for (DWORD i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
	{
		int keycode = keyEvents[i].dwOfs;
		int keystate = keyEvents[i].dwData;
		if ((keystate & 0x80) > 0)
			keyboardHandler->onKeyPress(keycode);
		else
			keyboardHandler->onKeyRelease(keycode);
	}
}
#include "helperFunction.h"
#include "DxKeyboard.h"
#include "DxGraph.h"
#include "DxInput.h"
#include "DxMouse.h"

LPDXINPUT DxInput::instance = NULL;

DxInput::DxInput()
{
	directInput = NULL;
	directMouse = new DxMouse();
	directKeyboard = new DxKeyboard();
}

DxInput::~DxInput()
{
	delete directMouse;
	delete directKeyboard;
	if (directInput != NULL)
		directInput->Release();
}

LPDXINPUT DxInput::getInstance()
{
	if (instance == NULL)
		instance = new DxInput();
	return instance;
}

bool DxInput::initializeDirectInput()
{
	HWND hWnd = DxGraph::getInstance()->getWindowHandler();
	HRESULT result = DirectInput8Create(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		DIRECTINPUT_VER,
		IID_IDirectInput8,
		(VOID**)&directInput, NULL
	);
	if (result != DI_OK)
	{
		showBug((wchar_t*)"L[ERROR]: Create DirectInput unsuccesfull\n");
		return false;
	}
	return true;
}

bool DxInput::initialize(LPKEYEVENTHANDLER keyhandler, LPMOUSEEVENTHANDLER mousehandler)
{
	if (!initializeDirectInput())
		return false;
	if (!directMouse->initialize(mousehandler, directInput))
		return false;
	if (!directKeyboard->initialize(keyhandler, directInput))
		return false;
	return true;
}

void DxInput::processInput()
{
	directMouse->process();
	directKeyboard->process();
}
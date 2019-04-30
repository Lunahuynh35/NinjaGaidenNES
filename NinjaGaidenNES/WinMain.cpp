#pragma region Your Modification
#define APPLICATION_TITLE L"NINJA GAIDEN"
#define FULLSCREEN 0
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define MAX_FRAME_PER_SEC 120
#pragma endregion

#include "helperFunction.h"
#include "DxGraph.h"
#include "DxInput.h"
#include "gameInputHandler.h"
#include "GameWorld.h"
#include "TextureCollection.h"

LPDXGRAPH directGraph;
LPDXINPUT directInput;
LPGAMEMH gameMouseHandler;
LPGAMEKH gameKeyHandler;
LPTEXTURES texturesCollection;
LPGAMEWORLD gameWorld;

ATOM registerMyWindowClass(HINSTANCE hInstance);
HWND createGameWindow(HINSTANCE hInstance, int nCmdShow);
void loopMainMessage();
bool loadResourceCollection();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd = createGameWindow(hInstance, nCmdShow);
	if (!showWindow(hWnd, nCmdShow))
		return 1;

	directGraph = DxGraph::getInstance();
	if (!directGraph->initialize(hWnd, FULLSCREEN))
		return 1;

	directInput = DxInput::getInstance();
	gameMouseHandler = new GameMouseHandler();
	gameKeyHandler = new GameKeyHandler();
	if (!directInput->initialize(gameKeyHandler, gameMouseHandler))
		return 1;

	texturesCollection = TextureCollection::getInstance();
	if (!loadResourceCollection())
		return 1;

	gameWorld = GameWorld::getInstance();
	if (!gameWorld->initialize())
		return 1;

	loopMainMessage();

	delete gameWorld;
	delete texturesCollection;
	delete gameKeyHandler;
	delete gameMouseHandler;
	delete directInput;
	delete directGraph;
	return 0;
}

#pragma region Your Modification
bool loadResourceCollection()
{
	texturesCollection->addTexture(
		STAGE3_1_TEXTUREID, L"Resource/Stage3-1_tileset.bmp", TRANSPARENCE_COLOR);
	texturesCollection->addTexture(
		STAGE3_2_TEXTUREID, L"Resource/Stage3-2_tileset.bmp", TRANSPARENCE_COLOR);
	texturesCollection->addTexture(
		STAGE3_3_TEXTUREID, L"Resource/Stage3-3_tileset.bmp", TRANSPARENCE_COLOR);
	return true;
}
#pragma endregion

void loopMainMessage()
{
	bool isDone = false;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_PER_SEC;

	while (!isDone)
	{
		isDone = isNoQuitMessageInQueue();

		DWORD now = GetTickCount();
		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD deltaTime = now - frameStart;

		if (deltaTime >= tickPerFrame)
		{
			frameStart = now;

			directInput->processInput();

			gameWorld->updateAfterDeltaTime(deltaTime / 1000.f);

			gameWorld->render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
	};
}

ATOM registerMyWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)processMessage;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPLICATION_TITLE;
	wc.hIconSm = NULL;

	return RegisterClassEx(&wc);
}

HWND createGameWindow(HINSTANCE hInstance, int nCmdShow)
{
	registerMyWindowClass(hInstance);

	DWORD ScreenMode;
	if (FULLSCREEN != 0)
		ScreenMode = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		ScreenMode = WS_TILEDWINDOW;

	HWND hWnd = CreateWindow(
		APPLICATION_TITLE, APPLICATION_TITLE,
		ScreenMode,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL
	);

	if (!hWnd)
	{
		showBug((wchar_t*)L"[ERROR]: Create Game window unsuccesfull\n");
		return FALSE;
	}

	return hWnd;
}
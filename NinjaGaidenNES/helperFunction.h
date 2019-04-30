#pragma once

struct BroadphaseBox;
typedef struct BroadphaseBox BROADBOX;

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>
#include <vector>

struct BroadphaseBox
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
};

void showBug(wchar_t * format, ...);
bool isNoQuitMessageInQueue();
bool showWindow(HWND hWnd, int nCmdShow);
LRESULT WINAPI processMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
D3DXVECTOR2 getWindowClientSize(HWND hWnd);
D3DPRESENT_PARAMETERS createDirect3dDeviceParameters(HWND hWnd, bool fullscreen);
D3DXVECTOR2 transformWorldPosToViewPos(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP);
D3DXVECTOR2 transformCenterPosToBotLeft(D3DXVECTOR2 obj_wP, D3DXVECTOR2 obj_size, D3DXVECTOR2 obj_cen);
bool checkAABB_BroadphaseBox(BROADBOX broadBox1, BROADBOX broadBox2);
DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize);
D3DXVECTOR2 getSizeOfTexture(LPDIRECT3DTEXTURE9 texture);
std::vector<std::string> getAllLineInTextFile(std::string path);
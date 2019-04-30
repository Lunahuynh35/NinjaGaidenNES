#include "helperFunction.h"
#include <stdio.h>	
#include <fstream>
#include <iostream>

void showBug(wchar_t * format, ...)
{
	va_list argp;
	va_start(argp, format);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, format, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

bool isNoQuitMessageInQueue()
{
	MSG message;
	bool isDone = false;
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
			isDone = true;
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return isDone;
}

bool showWindow(HWND hWnd, int nCmdShow)
{
	if (!hWnd)
		return false;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}

LRESULT WINAPI processMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

D3DXVECTOR2 getWindowClientSize(HWND hWnd)
{
	D3DXVECTOR2 windowSize;
	RECT windowRect;
	GetClientRect(hWnd, &windowRect);
	windowSize.x = (float)windowRect.right - windowRect.left;
	windowSize.y = (float)windowRect.bottom - windowRect.top;
	return windowSize;
}

D3DPRESENT_PARAMETERS createDirect3dDeviceParameters(HWND hWnd, bool fullscreen)
{
	D3DXVECTOR2 windowSize = getWindowClientSize(hWnd);

	D3DPRESENT_PARAMETERS direct3dDeviceParameters;
	ZeroMemory(&direct3dDeviceParameters, sizeof(direct3dDeviceParameters));
	direct3dDeviceParameters.Windowed = (!fullscreen);
	direct3dDeviceParameters.SwapEffect = D3DSWAPEFFECT_COPY;
	direct3dDeviceParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	direct3dDeviceParameters.BackBufferCount = 1;
	direct3dDeviceParameters.BackBufferWidth = (int)windowSize.x;
	direct3dDeviceParameters.BackBufferHeight = (int)windowSize.y;
	direct3dDeviceParameters.hDeviceWindow = hWnd;

	return direct3dDeviceParameters;
}

D3DXVECTOR2 transformWorldPosToViewPos(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP)
{
	D3DXMATRIX matrixTransform;
	D3DXMatrixIdentity(&matrixTransform);
	matrixTransform._22 = -1.f;
	matrixTransform._41 = -cam_wP.x;
	matrixTransform._42 = cam_wP.y;

	D3DXVECTOR3 obj_wP_3D(obj_wP.x, obj_wP.y, 0);
	D3DXVECTOR4 result;

	D3DXVec3Transform(&result, &obj_wP_3D, &matrixTransform);

	return D3DXVECTOR2(result.x, result.y);
}

D3DXVECTOR2 transformCenterPosToBotLeft(D3DXVECTOR2 obj_wP, D3DXVECTOR2 obj_size, D3DXVECTOR2 obj_cen)
{
	D3DXMATRIX mtTrans;
	D3DXVECTOR3 obj_wp(obj_wP.x, obj_wP.y, 0);
	D3DXVECTOR4 result;

	D3DXMatrixIdentity(&mtTrans);
	mtTrans._41 = -obj_cen.x;
	mtTrans._42 = obj_cen.y - obj_size.y;
	D3DXVec3Transform(&result, &obj_wp, &mtTrans);

	return D3DXVECTOR2(result.x, result.y);
}

bool checkAABB_BroadphaseBox(BROADBOX broadBox1, BROADBOX broadBox2)
{
	if (broadBox1.position.x + broadBox1.size.x <= broadBox2.position.x)
		return false;
	if (broadBox1.position.x >= broadBox2.position.x + broadBox2.size.x)
		return false;
	if (broadBox1.position.y + broadBox1.size.y <= broadBox2.position.y)
		return false;
	if (broadBox1.position.y >= broadBox2.position.y + broadBox2.size.y)
		return false;
	return true;
}

DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize)
{
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = bufferSize;
	return dipdw;
}

D3DXVECTOR2 getSizeOfTexture(LPDIRECT3DTEXTURE9 texture)
{
	D3DSURFACE_DESC surfaceDesc;
	texture->GetLevelDesc(0, &surfaceDesc);
	return D3DXVECTOR2(surfaceDesc.Width, surfaceDesc.Height);
}

std::vector<std::string> getAllLineInTextFile(std::string path)
{
	std::vector<std::string> lines;
	std::string line;
	std::ifstream myTextFile(path);
	if (myTextFile.is_open())
	{
		while (getline(myTextFile, line))
			lines.push_back(line);
		myTextFile.close();
	}

	return lines;
}

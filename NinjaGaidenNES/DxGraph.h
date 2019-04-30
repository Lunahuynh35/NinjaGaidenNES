#pragma once

class DxGraph;
typedef class DxGraph * LPDXGRAPH;

#include <d3d9.h>
#include <d3dx9.h>

class DxGraph
{
private:
	static LPDXGRAPH instance;
	HWND windowHandler;
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 direct3dDevice;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;
	D3DXVECTOR2 clientSize;

	DxGraph();
	bool initializeDirect3d();
	bool initializeDirect3dDevice(HWND hWnd, bool fullscreen);

public:
	~DxGraph();
	static LPDXGRAPH getInstance();
	HWND getWindowHandler();
	LPDIRECT3DDEVICE9 getDirect3dDevice();
	LPDIRECT3DSURFACE9 getBackbuffer();
	LPD3DXSPRITE getSpriteHandler();
	D3DXVECTOR2 getClientSize();
	bool initialize(HWND hWnd, bool fullscreen);
	static LPDIRECT3DTEXTURE9 loadTexture(LPCWSTR filename, D3DCOLOR transcolor);
	static LPDIRECT3DSURFACE9 createSurface(int width, int height);
};
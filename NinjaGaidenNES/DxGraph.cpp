#include "DxGraph.h"
#include "helperFunction.h"

LPDXGRAPH DxGraph::instance = NULL;

LPDXGRAPH DxGraph::getInstance()
{
	if (instance == NULL)
		instance = new DxGraph();
	return instance;
}

DxGraph::DxGraph()
{
	windowHandler = NULL;
	direct3d = NULL;
	direct3dDevice = NULL;
	backBuffer = NULL;
	spriteHandler = NULL;
}

DxGraph::~DxGraph()
{
	if (spriteHandler != NULL)
		spriteHandler->Release();
	if (backBuffer != NULL)
		backBuffer->Release();
	if (direct3dDevice != NULL)
		direct3dDevice->Release();
	if (direct3d != NULL)
		direct3d->Release();
}

bool DxGraph::initializeDirect3d()
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
	{
		showBug((wchar_t*)L"[ERROR]: Create Direct3D unsuccessfull\n");
		return false;
	}
	return true;
}

bool DxGraph::initializeDirect3dDevice(HWND hWnd, bool fullscreen)
{
	D3DPRESENT_PARAMETERS direct3dDeviceParameters =
		createDirect3dDeviceParameters(hWnd, fullscreen);

	clientSize.x = (float)direct3dDeviceParameters.BackBufferWidth;
	clientSize.y = (float)direct3dDeviceParameters.BackBufferHeight;

	direct3d->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&direct3dDeviceParameters,
		&direct3dDevice
	);

	if (direct3dDevice == NULL)
	{
		showBug((wchar_t*)L"[ERROR]: Create Direct3D Device unsuccessfull\n");
		return false;
	}

	return true;
}

HWND DxGraph::getWindowHandler()
{
	return windowHandler;
}

LPDIRECT3DDEVICE9 DxGraph::getDirect3dDevice()
{
	return direct3dDevice;
}

LPDIRECT3DSURFACE9 DxGraph::getBackbuffer()
{
	return backBuffer;
}

LPD3DXSPRITE DxGraph::getSpriteHandler()
{
	return spriteHandler;
}

D3DXVECTOR2 DxGraph::getClientSize()
{
	return clientSize;
}

bool DxGraph::initialize(HWND hWnd, bool fullscreen)
{
	windowHandler = hWnd;

	if (!initializeDirect3d())
		return false;

	if (!initializeDirect3dDevice(hWnd, fullscreen))
		return false;

	direct3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	direct3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	D3DXCreateSprite(direct3dDevice, &spriteHandler);

	return true;
}

LPDIRECT3DTEXTURE9 DxGraph::loadTexture(LPCWSTR filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO imageInfo;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &imageInfo);
	if (result != D3D_OK)
	{
		showBug((wchar_t*)L"[ERROR]: Get image info unsuccesfull: %s", filename);
		return NULL;
	}

	result = D3DXCreateTextureFromFileEx(
		instance->direct3dDevice, filename,
		imageInfo.Width, imageInfo.Height,
		1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		transcolor, &imageInfo, NULL, &texture
	);

	if (result != D3D_OK)
	{
		showBug((wchar_t*)"[ERROR]: Create texture unsuccesfull: %s", filename);
		return NULL;
	}

	return texture;
}

LPDIRECT3DSURFACE9 DxGraph::createSurface(int width, int height)
{
	LPDIRECT3DSURFACE9 surface;
	instance->direct3dDevice->CreateOffscreenPlainSurface(
		width, height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface, NULL
	);
	return surface;
}
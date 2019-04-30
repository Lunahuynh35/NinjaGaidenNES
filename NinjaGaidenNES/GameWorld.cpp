#include "GameWorld.h"
#include "DxGraph.h"

LPGAMEWORLD GameWorld::instance = NULL;

#pragma region Your Code

bool GameWorld::initialize()
{
	clientSize = DxGraph::getInstance()->getClientSize();
	setCameraPosition(0, clientSize.y);

	loadResource();

	return true;
}

void GameWorld::updateAfterDeltaTime(float deltaT)
{

}

void GameWorld::finish()
{

}

void GameWorld::render()
{
	LPDIRECT3DDEVICE9 direct3dDevice = DxGraph::getInstance()->getDirect3dDevice();
	LPDIRECT3DSURFACE9 backBuffer = DxGraph::getInstance()->getBackbuffer();
	LPD3DXSPRITE spriteHandler = DxGraph::getInstance()->getSpriteHandler();

	if (direct3dDevice->BeginScene())
	{
		//Clear backbuffer with a color
		direct3dDevice->ColorFill(backBuffer, NULL, BACKBUFFER_CLEAR_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//
		// Call render function of all gameObject in game world
		//


		//
		//
		//
		spriteHandler->End();
		direct3dDevice->EndScene();
	}
	direct3dDevice->Present(NULL, NULL, NULL, NULL);
}

bool GameWorld::loadResource()
{

	return true;
}

GameWorld::~GameWorld()
{

}

GameWorld::GameWorld()
{

}

#pragma endregion

void GameWorld::setCameraPosition(float x, float y)
{
	camera_wP.x = x;
	camera_wP.y = y;
}

D3DXVECTOR2 GameWorld::getCameraPosition()
{
	return camera_wP;
}

LPGAMEWORLD GameWorld::getInstance()
{
	if (instance == NULL)
		instance = new GameWorld();
	return instance;
}
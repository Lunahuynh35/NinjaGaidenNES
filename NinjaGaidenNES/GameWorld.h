#pragma once

#define BACKBUFFER_CLEAR_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define TRANSPARENCE_COLOR D3DCOLOR_XRGB(255, 0, 255)

class GameWorld;
typedef class GameWorld * LPGAMEWORLD;

#include <d3dx9.h>

class GameWorld
{
private:
	static LPGAMEWORLD instance;
	D3DXVECTOR2 camera_wP;
	D3DXVECTOR2 clientSize;
	// Put your game object

	//
	GameWorld();
	bool loadResource();

public:
	~GameWorld();
	static LPGAMEWORLD getInstance();
	bool initialize();

	void setCameraPosition(float x, float y);
	D3DXVECTOR2 getCameraPosition();

	void updateAfterDeltaTime(float deltaT);
	void finish();
	void render();
};
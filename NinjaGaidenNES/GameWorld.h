#pragma once

#define BACKBUFFER_CLEAR_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define TRANSPARENCE_COLOR D3DCOLOR_XRGB(255, 163, 177)

class GameWorld;
typedef class GameWorld * LPGAMEWORLD;

#include <d3dx9.h>
#include "TileMap.h"
#include "MainCharacter.h"

class GameWorld
{
private:
	static LPGAMEWORLD instance;
	D3DXVECTOR2 camera_wP;
	D3DXVECTOR2 clientSize;
	// Put your game object
	LPTILEMAP stage3_1_Map;

	LPMAINCHAR mainCharacter;
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
	void updateCameraPosition();
	void finish();
	void render();
};
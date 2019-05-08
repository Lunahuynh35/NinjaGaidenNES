#pragma once

#define STAGE3_1_TEXTUREID 0001
#define STAGE3_2_TEXTUREID 0002
#define STAGE3_3_TEXTUREID 0003
#define STAGE3_1_MATRIXFILE "Resource/Maps/Stage3-1_matrixmap.txt"
#define STAGE3_2_MATRIXFILE "Resource/Maps/Stage3-2_matrixmap.txt"
#define STAGE3_3_MATRIXFILE "Resource/Maps/Stage3-3_matrixmap.txt"

class TileMap;
typedef class TileMap * LPTILEMAP;
class Sprite;
typedef class Sprite * LPSPRITE;

enum Stage
{
	_3_1 = 1,
	_3_2 = 2,
	_3_3 = 3
};

#include "GameObject.h"
#include <vector>

class TileMap : public GameObject
{
private:
	D3DXVECTOR2 size = D3DXVECTOR2(0, 0);
	Stage stageMap;
	std::vector<LPSPRITE> tileset;
	std::vector<std::vector<int>> matrixMap;
public:
	TileMap(Stage stage);
	~TileMap();
	void loadResource();
	D3DXVECTOR2 getSize();
	void render(D3DXVECTOR2 cam_wP);
	void updateAfterDeltaTime(float deltaT) {}
	BoundBox getBoundBox(float dt);
};
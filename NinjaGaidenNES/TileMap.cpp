#include "TileMap.h"
#include "BoundBox.h"
#include "TextureCollection.h"
#include "helperFunction.h"
#include "Sprite.h"
#include <sstream>

TileMap::TileMap(Stage stage)
{
	stageMap = stage;
}

TileMap::~TileMap()
{
	for (int i = 0; i < tileset.size(); i++)
		delete tileset[i];
}

void TileMap::loadResource()
{
	std::vector<std::string> matrixFileLines;
	LPDIRECT3DTEXTURE9 texture;
	LPSPRITE tempSprite;
	switch (stageMap)
	{
	case _3_1:
		texture = TextureCollection::getInstance()->getTexture(STAGE3_1_TEXTUREID);
		matrixFileLines = getAllLineInTextFile(STAGE3_1_MATRIXFILE);
		break;
	case _3_2:
		texture = TextureCollection::getInstance()->getTexture(STAGE3_2_TEXTUREID);
		matrixFileLines = getAllLineInTextFile(STAGE3_2_MATRIXFILE);
		break;
	default:
		texture = TextureCollection::getInstance()->getTexture(STAGE3_3_TEXTUREID);
		matrixFileLines = getAllLineInTextFile(STAGE3_3_MATRIXFILE);
		break;
	}

	int tilesetRows = getSizeOfTexture(texture).y / 16;
	int tilesetCols = getSizeOfTexture(texture).x / 16;

	for(int i = 0; i < tilesetRows; i++)
		for (int j = 0; j < tilesetCols; j++)
		{
			tempSprite = new Sprite(texture, 
				i * 16, j * 16, (j + 1) * 16, (i + 1) * 16);
			tileset.push_back(tempSprite);
		}

	for (int i = 0; i < matrixFileLines.size(); i++)
	{
		std::vector<int> tempLine;
		int number;
		std::stringstream iss(matrixFileLines[i]);
		while (iss >> number)
			tempLine.push_back(number);
		matrixMap.push_back(tempLine);
	}
	size.x = matrixMap[0].size() * 16;
	size.y = matrixMap.size() * 16;
}

D3DXVECTOR2 TileMap::getSize()
{
	return size;
}

void TileMap::render(D3DXVECTOR2 cam_wP)
{
	// begin render from left top
	// postion is left top
	D3DXVECTOR2 obj_vP = transformWorldPosToViewPos(position, cam_wP);
	for (int i = 0; i < matrixMap.size(); i++)
		for (int j = 0; j < matrixMap[i].size(); j++)
			tileset[matrixMap[i][j]]->draw(obj_vP + D3DXVECTOR2(j * 16, i * 16));
}

BoundBox TileMap::getBoundBox(float dt)
{
	return BoundBox();
}

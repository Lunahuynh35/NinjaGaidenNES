#pragma once

class TextureCollection;
typedef class TextureCollection * LPTEXTURES;

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>

class TextureCollection
{
private:
	static LPTEXTURES instance;
	std::vector<int> ids;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textureCollection;
	TextureCollection() {}

public:
	~TextureCollection();
	static LPTEXTURES getInstance();
	bool addTexture(int id, LPCWSTR filename, D3DCOLOR transparent);
	LPDIRECT3DTEXTURE9 getTexture(int id);
};
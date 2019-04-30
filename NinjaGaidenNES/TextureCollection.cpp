#include "TextureCollection.h"
#include "helperFunction.h"
#include "DxGraph.h"

LPTEXTURES TextureCollection::instance = NULL;

TextureCollection::~TextureCollection()
{
	for (unsigned int i = 0; i < ids.size(); i++)
		textureCollection[ids[i]]->Release();
}

LPTEXTURES TextureCollection::getInstance()
{
	if (instance == NULL)
		instance = new TextureCollection();
	return instance;
}

bool TextureCollection::addTexture(int id, LPCWSTR filename, D3DCOLOR transparent)
{
	for (unsigned int i = 0; i < ids.size(); i++)
		if (id == ids[i])
		{
			showBug((wchar_t*)L"[WARNING]: Texture ID \"%d\" existed\n", id);
			return false;
		}
	LPDIRECT3DTEXTURE9 texture = DxGraph::loadTexture(filename, transparent);
	if (texture == NULL)
	{
		showBug((wchar_t*)L"[WARNING]: Can't load texture from file: %s\n", filename);
		return false;
	}
	ids.push_back(id);
	textureCollection[id] = texture;
	return true;
}

LPDIRECT3DTEXTURE9 TextureCollection::getTexture(int id)
{
	for (unsigned int i = 0; i < ids.size(); i++)
		if (id == ids[i])
			return textureCollection[id];
	showBug((wchar_t*)L"[WARNING]: Texture collection doesn't have ID \"%d\"\n", id);
	return NULL;
}
#pragma once

class Sprite;
typedef class Sprite * LPSPRITE;

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>

class Sprite
{
private:
	RECT rectbound;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR2 size;
	D3DXVECTOR2 center;
	D3DXMATRIX transformMatrix;
public:
	Sprite(LPDIRECT3DTEXTURE9 texture, 
		int top, int left, int right, int bot,
		int cX = 0, int cY = 0);
	~Sprite() {};
	D3DXVECTOR2 getSize();
	D3DXVECTOR2 getCenter();
	void setTransform(bool flipX, bool flipY, D3DXVECTOR2 scaleSize);
	void draw(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP);
	void draw(D3DXVECTOR2 obj_vP);
};
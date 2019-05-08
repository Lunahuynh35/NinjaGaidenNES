#pragma once

class Animation;
typedef class Animation * LPANIMATION;
class Sprite;
typedef class Sprite * LPSPRITE;

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>

class Animation
{
private:
	DWORD lastframetime;
	int betweenframetime;
	int currentframe;
	std::vector<LPSPRITE> frames;

public:
	Animation(int betweentime);
	~Animation();
	void addFrameSprite(LPSPRITE sprite);
	void render(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP);
	D3DXVECTOR2 getSizeCurFrame();
	D3DXVECTOR2 getCenterCurFrame();
	void setTransform(bool flipX, bool flipY, D3DXVECTOR2 scaleSize);
};

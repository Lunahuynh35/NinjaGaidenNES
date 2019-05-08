#include "Animation.h"
#include "Sprite.h"

Animation::Animation(int betweentime)
{
	betweenframetime = betweentime;
	currentframe = -1;
	lastframetime = -1;
}

Animation::~Animation()
{
	for (unsigned int i = 0; i < frames.size(); i++)
		delete frames[i];
}

void Animation::addFrameSprite(LPSPRITE sprite)
{
	if (sprite == NULL)
		return;
	frames.push_back(sprite);
}

void Animation::render(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP)
{
	currentframe = currentframe == -1 ? 0 : currentframe;
	DWORD now = GetTickCount();
	frames[currentframe]->draw(obj_wP, cam_wP);
	if (now - lastframetime > (DWORD)betweenframetime)
	{
		currentframe = (currentframe + 1) % frames.size();
		lastframetime = now;
	}
}

D3DXVECTOR2 Animation::getSizeCurFrame()
{
	if (currentframe == -1)
		return D3DXVECTOR2(0, 0);
	return frames[currentframe]->getSize();
}

D3DXVECTOR2 Animation::getCenterCurFrame()
{
	if (currentframe == -1)
		return D3DXVECTOR2(0, 0);
	return frames[currentframe]->getCenter();
}

void Animation::setTransform(bool flipX, bool flipY, D3DXVECTOR2 scaleSize)
{
	for (int i = 0; i < frames.size(); i++)
		frames[i]->setTransform(flipX, flipY, scaleSize);
}

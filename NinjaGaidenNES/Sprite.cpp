#include "helperFunction.h"
#include "DxGraph.h"
#include "Sprite.h"

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, int top, int left, int right, int bot, int cX, int cY)
{
	this->texture = texture;
	rectbound.top = top;
	rectbound.left = left;
	rectbound.right = right;
	rectbound.bottom = bot;
	if ((cX | cY) == 0)
	{
		center.x = (right - left) / 2.f;
		center.y = (bot - top) / 2.f;
	}
	else
		center = D3DXVECTOR2((float)cX, (float)cY);
	setTransform(false, false, D3DXVECTOR2(1, 1));
}

D3DXVECTOR2 Sprite::getSize()
{
	return size;
}

D3DXVECTOR2 Sprite::getCenter()
{
	D3DXVECTOR2 centerReturn;
	centerReturn.x = center.x * abs(transformMatrix._11);
	centerReturn.y = center.y * abs(transformMatrix._22);
	return centerReturn;
}

void Sprite::setTransform(bool flipX, bool flipY, D3DXVECTOR2 scaleSize)
{
	float tempFlipX = flipX ? -1.f : 1.f;
	float tempFlipY = flipY ? -1.f : 1.f;
	D3DXMatrixScaling(&transformMatrix, tempFlipX * scaleSize.x, tempFlipY * scaleSize.y, 1);
	size.x = (rectbound.right - rectbound.left) * scaleSize.x;
	size.y = (rectbound.bottom - rectbound.top) * scaleSize.y;
}

void Sprite::draw(D3DXVECTOR2 obj_wP, D3DXVECTOR2 cam_wP)
{
	D3DXVECTOR2 obj_vP = transformWorldPosToViewPos(obj_wP, cam_wP);
	D3DXMATRIX transform;
	D3DXMatrixTranslation(&transform, obj_vP.x, obj_vP.y, 0.f);
	transform = transformMatrix * transform;

	LPD3DXSPRITE spriteHandler = DxGraph::getInstance()->getSpriteHandler();

	spriteHandler->SetTransform(&transform);
	spriteHandler->Draw(
		texture,
		&rectbound,
		&D3DXVECTOR3(center.x, center.y, 0),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::draw(D3DXVECTOR2 obj_vP)
{
	D3DXMATRIX transform;
	D3DXMatrixTranslation(&transform, obj_vP.x, obj_vP.y, 0.f);
	transform = transformMatrix * transform;

	LPD3DXSPRITE spriteHandler = DxGraph::getInstance()->getSpriteHandler();

	spriteHandler->SetTransform(&transform);
	spriteHandler->Draw(
		texture,
		&rectbound,
		&D3DXVECTOR3(center.x, center.y, 0),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

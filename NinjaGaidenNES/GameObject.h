#pragma once

class BoundBox;
class GameObject;
typedef class GameObject * LPGAMEOBJECT;

#include <d3dx9.h>

class GameObject
{
protected:
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 size;
public:
	GameObject() {};
	~GameObject() {};
	void setPosition(float x, float y);
	void setVelocity(float x, float y);
	void setSize(float x, float y);
	D3DXVECTOR2 getPosition();
	D3DXVECTOR2 getVelocity();
	D3DXVECTOR2 getSize();
	virtual void loadResource() = 0;
	virtual void render(D3DXVECTOR2 cam_wP) = 0;
	virtual void updateAfterDeltaTime(float deltaT) = 0;
	virtual BoundBox getBoundBox(float dt) = 0;
};
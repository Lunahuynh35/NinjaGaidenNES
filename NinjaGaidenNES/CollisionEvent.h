#pragma once

class GameObject;
class CollisionEvent;
typedef class GameObject * LPGAMEOBJECT;
typedef class CollisionEvent * LPCOLLIEVENT;

#include <d3dx9.h>
#include <vector>

class CollisionEvent
{
public:
	float timecolli;
	LPGAMEOBJECT gameobj;
	D3DXVECTOR2 normalVector;
	CollisionEvent(float time, D3DXVECTOR2 normal, LPGAMEOBJECT obj = NULL);
	static bool compare(LPCOLLIEVENT &a, LPCOLLIEVENT &b);
};
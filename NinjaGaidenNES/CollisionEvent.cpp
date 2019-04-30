#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(float time, D3DXVECTOR2 normal, LPGAMEOBJECT obj)
{
	gameobj = obj;
	timecolli = time;
	normalVector = normal;
}

bool CollisionEvent::compare(LPCOLLIEVENT & a, LPCOLLIEVENT & b)
{
	return a->timecolli < b->timecolli;
}
#pragma once

class InteractiveObject;
class CollisionEvent;
typedef class CollisionEvent * LPCOLLIEVENT;

#include "GameObject.h"
#include <vector>

class InteractiveObject : public GameObject
{
protected:
	LPCOLLIEVENT sweptAABBex(LPGAMEOBJECT coObj, float dt);
public:
	InteractiveObject() {};
	~InteractiveObject() {};
	void calcPotentialColli(float dt,
		std::vector<LPGAMEOBJECT> * coObjs,
		std::vector<LPCOLLIEVENT> &coEvents);
};
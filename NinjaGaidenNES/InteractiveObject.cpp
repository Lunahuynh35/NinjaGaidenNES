#include "InteractiveObject.h"
#include "CollisionDetector.h"
#include "CollisionEvent.h"
#include "BoundBox.h"

LPCOLLIEVENT InteractiveObject::sweptAABBex(LPGAMEOBJECT coObj, float dt)
{
	BoundBox sObjBBox = coObj->getBoundBox(dt);
	BoundBox mObjBBox = this->getBoundBox(dt);
	D3DXVECTOR2 normal;

	float time = CollisionDetector::sweptAABB(mObjBBox, sObjBBox, normal);

	LPCOLLIEVENT e = new CollisionEvent(time, normal, coObj);
	return e;
}

void InteractiveObject::calcPotentialColli(float dt, std::vector<LPGAMEOBJECT>* coObjs, std::vector<LPCOLLIEVENT>& coEvents)
{
	for (unsigned int i = 0; i < coObjs->size(); i++)
	{
		LPCOLLIEVENT e = sweptAABBex(coObjs->at(i), dt);
		if (e->timecolli == 1.0f && e->normalVector == D3DXVECTOR2(0, 0))
			delete e;
		else
			coEvents.push_back(e);
	}
}

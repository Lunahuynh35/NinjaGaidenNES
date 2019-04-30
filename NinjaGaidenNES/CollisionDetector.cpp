#include "CollisionDetector.h"
#include "CollisionEvent.h"
#include "helperFunction.h"
#include "BoundBox.h"

float CollisionDetector::sweptAABB(BoundBox mObj, BoundBox sObj, D3DXVECTOR2 & normal)
{
	// normal = (0,0) && time = 1.0f is no collision
	normal = D3DXVECTOR2(0, 0);
	BROADBOX bpb_mO = mObj.getSweptBroadphaseBox();
	BROADBOX bpb_sO = sObj.getSweptBroadphaseBox();

	// Broadphase box don't intersect
	if (!checkAABB_BroadphaseBox(bpb_mO, bpb_sO))
		return 1.0f;

	// normal = (0,0) & time = 0.0f is Objs intersected before call this function
	if (mObj.displayment == D3DXVECTOR2(0, 0) && sObj.displayment == D3DXVECTOR2(0, 0))
		return 0.0f;

	// Relativity of velocity
	mObj.displayment -= sObj.displayment;
	sObj.displayment = D3DXVECTOR2(0, 0);

	// Calculate distance of 2 near side and 2 far side
	D3DXVECTOR2 InvEntry(0, 0);
	D3DXVECTOR2 InvExit(0, 0);

	if (mObj.displayment.x > 0)
	{
		InvEntry.x = sObj.position.x - (mObj.position.x + mObj.size.x);
		InvExit.x = (sObj.position.x + sObj.size.x) - mObj.position.x;
	}
	else if (mObj.displayment.x < 0)
	{
		InvEntry.x = (sObj.position.x + sObj.size.x) - mObj.position.x;
		InvExit.x = sObj.position.x - (mObj.position.x + mObj.size.x);
	}

	if (mObj.displayment.y > 0)
	{
		InvEntry.y = sObj.position.y - (mObj.position.y + mObj.size.y);
		InvExit.y = (sObj.position.y + sObj.size.y) - mObj.position.y;
	}
	else if (mObj.displayment.y < 0)
	{
		InvEntry.y = (sObj.position.y + sObj.size.y) - mObj.position.y;
		InvExit.y = sObj.position.y - (mObj.position.y + mObj.size.y);
	}

	// Calculate time entry, exit of each pair of side
	D3DXVECTOR2 EntryT(0, 0);
	D3DXVECTOR2 ExitT(0, 0);

	if (mObj.displayment.x == 0)
	{
		EntryT.x = -std::numeric_limits<float>::infinity();
		ExitT.x = std::numeric_limits<float>::infinity();
	}
	else
	{
		EntryT.x = InvEntry.x / mObj.displayment.x;
		ExitT.x = InvExit.x / mObj.displayment.x;
	}

	if (mObj.displayment.y == 0)
	{
		EntryT.y = -std::numeric_limits<float>::infinity();
		ExitT.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		EntryT.y = InvEntry.y / mObj.displayment.y;
		ExitT.y = InvExit.y / mObj.displayment.y;
	}

	float entryTime = max(EntryT.x, EntryT.y);
	float exitTime = min(ExitT.x, ExitT.y);

	if (entryTime > exitTime || EntryT.x > 1.0f || EntryT.y > 1.0f)
		return 1.0f;

	if (entryTime < 0.0f)
	{
		if (abs(entryTime) >= exitTime)
			return 1.0f;
		else
			entryTime = 0.0f;
	}

	if (EntryT.x > EntryT.y)
		normal.x = mObj.displayment.x < 0.0f ? 1.0f : -1.0f;
	else if (EntryT.x == EntryT.y)
	{
		normal.x = mObj.displayment.x < 0.0f ? 1.0f : -1.0f;
		normal.y = mObj.displayment.y < 0.0f ? 1.0f : -1.0f;
	}
	else
		normal.y = mObj.displayment.y < 0.0f ? 1.0f : -1.0f;

	return entryTime;
}

void CollisionDetector::filterCollision(
	std::vector<LPCOLLIEVENT>& ColliEvents, 
	std::vector<LPCOLLIEVENT>& ColliEventsRes,
	float & min_tX, float & min_tY, D3DXVECTOR2 & normal)
{
	min_tX = 1.0f;
	min_tY = 1.0f;
	int iMinX = -1;
	int iMinY = -1;

	normal = D3DXVECTOR2(0, 0);
	ColliEventsRes.clear();

	for (unsigned int i = 0; i < ColliEvents.size(); i++)
	{
		LPCOLLIEVENT c = ColliEvents[i];

		if (c->timecolli < min_tX && c->normalVector.x != 0)
		{
			min_tX = c->timecolli;
			normal.x = c->normalVector.x;
			iMinX = i;
		}
		if (c->timecolli < min_tY && c->normalVector.y != 0)
		{
			min_tY = c->timecolli;
			normal.y = c->normalVector.y;
			iMinY = i;
		}
	}
	if (min_tX < min_tY)
	{
		if (iMinX >= 0) ColliEventsRes.push_back(ColliEvents[iMinX]);
		if (iMinY >= 0) ColliEventsRes.push_back(ColliEvents[iMinY]);
		normal.y = 0;
	}
	else
	{
		if (iMinY >= 0) ColliEventsRes.push_back(ColliEvents[iMinY]);
		if (iMinX >= 0) ColliEventsRes.push_back(ColliEvents[iMinX]);
		normal.x = 0;
	}
}
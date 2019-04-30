#pragma once

class BoundBox;
class CollisionEvent;
class CollisionDetector;
typedef class CollisionEvent * LPCOLLIEVENT;

#include <d3dx9.h>
#include <vector>

class CollisionDetector
{
private:
	CollisionDetector() {}
public:
	static float sweptAABB(BoundBox mObj, BoundBox sObj, D3DXVECTOR2 &normal);
	static void filterCollision(
		std::vector<LPCOLLIEVENT> &ColliEvents, 
		std::vector<LPCOLLIEVENT> &ColliEventsRes,
		float &min_tX, float &min_tY, D3DXVECTOR2 &normal);
};
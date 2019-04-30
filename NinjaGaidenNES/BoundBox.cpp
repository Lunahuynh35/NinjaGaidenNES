#include "BoundBox.h"
#include "helperFunction.h"

BoundBox::BoundBox()
{
	position = D3DXVECTOR2(0, 0);
	size = D3DXVECTOR2(0, 0);
	displayment = D3DXVECTOR2(0, 0);
}

BROADBOX BoundBox::getSweptBroadphaseBox()
{
	BROADBOX res;

	if (displayment.x >= 0)
	{
		res.position.x = position.x;
		res.size.x = displayment.x + size.x;
	}
	else
	{
		res.position.x = position.x + displayment.x;
		res.size.x = size.x - displayment.x;
	}

	if (displayment.y >= 0)
	{
		res.position.y = position.y;
		res.size.y = displayment.y + size.y;
	}
	else
	{
		res.position.y = position.y + displayment.y;
		res.size.y = size.y - displayment.y;
	}

	return res;
}
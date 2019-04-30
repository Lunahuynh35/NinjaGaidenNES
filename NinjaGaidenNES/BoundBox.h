#pragma once

class BoundBox;
struct BroadphaseBox;
typedef struct BroadphaseBox BROADBOX;

#include <d3dx9.h>
#include <vector>

class BoundBox
{
public:
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	D3DXVECTOR2 displayment;
	BoundBox();
	BROADBOX getSweptBroadphaseBox();
};
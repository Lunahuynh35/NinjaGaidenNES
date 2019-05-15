#pragma once

class Node;
typedef class Node * LPNODE;
class Grid;
typedef class Grid * LPGRID;

#include <d3d9.h>
#include <vector>
#include <string>

class Node
{
private:
	int id;
	RECT rectangle;
	std::vector<int> objIDs;

public:
	void loadInfoFromString(std::string info);
	void updateAfterDeltaTime(float deltaT, LPGRID grid);
};
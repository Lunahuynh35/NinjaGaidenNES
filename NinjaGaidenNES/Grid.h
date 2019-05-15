#pragma once

#define STAGE3_1_GRID_FILE "Resource/Maps/Stage3-1_Grid1x14.txt"
#define STAGE3_1_OBJS_FILE "Resource/Maps/ObjectList_Stage3-1.txt"

class Grid;
typedef class Grid * LPGRID;
class Node;
typedef class Node * LPNODE;
class GameObject;
typedef class GameObject * LPGAMEOBJECT;

#include <vector>
#include <string>
#include <unordered_map>

class Grid
{
	friend class Node;

private:
	std::vector<LPNODE> cells;
	std::vector<int> objIDs;
	std::unordered_map<int, bool> isUpdatedObjs;
	std::unordered_map<int, LPGAMEOBJECT> gameObjects;

public:
	~Grid();
	void loadInfoFromFile();
	void updateAfterDeltaTime(float deltaT);
};
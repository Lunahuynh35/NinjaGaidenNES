#include "Node.h"
#include "Grid.h"
#include <sstream>
#include "DxGraph.h"
#include "GameWorld.h"
#include "helperFunction.h"
#include "TileMap.h"

void Node::loadInfoFromString(std::string info)
{
	int left, top, right, bot, number;
	findAndReplaceAll(info, ",", " ");
	std::stringstream iss(info);

	iss >> id;
	iss >> left;
	iss >> top;
	iss >> right;
	iss >> bot;

	left += BACKGROUND_DEFAULT_POSITION.x;
	right += BACKGROUND_DEFAULT_POSITION.x;
	top = BACKGROUND_DEFAULT_POSITION.y - top;
	bot = BACKGROUND_DEFAULT_POSITION.y - bot;

	rectangle.left = left;
	rectangle.right = right;
	rectangle.top = top;
	rectangle.bottom = bot;

	while(iss >> number)
		objIDs.push_back(number);
}

void Node::updateAfterDeltaTime(float deltaT, LPGRID grid)
{
	D3DXVECTOR2 camera = GameWorld::getInstance()->getCameraPosition();
	BROADBOX viewBox, nodeBox;
	viewBox.position = camera;
	viewBox.size = DxGraph::getInstance()->getClientSize();
	nodeBox.position.x = rectangle.left;
	nodeBox.position.y = rectangle.top;
	nodeBox.size.x = abs(rectangle.right - rectangle.left);
	nodeBox.size.y = abs(rectangle.bottom - rectangle.top);

	if (checkAABB_BroadphaseBox(nodeBox, viewBox))
		for (int i = 0; i < objIDs.size(); i++)
			if (!grid->isUpdatedObjs[objIDs[i]])
			{
				if(grid->gameObjects[objIDs[i]] != NULL)
					grid->gameObjects[objIDs[i]]->updateAfterDeltaTime(deltaT);
				grid->isUpdatedObjs[objIDs[i]] = true;
			}
}

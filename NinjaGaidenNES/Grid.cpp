#include "Grid.h"
#include "Node.h"
#include "helperFunction.h"
#include <sstream>

Grid::~Grid()
{
	for (int i = 0; i < cells.size(); i++)
		delete cells[i];
}

void Grid::loadInfoFromFile()
{
	std::vector<std::string> gridInfoLines = getAllLineInTextFile(STAGE3_1_GRID_FILE);
	for (int i = 0; i < gridInfoLines.size(); i++)
	{
		LPNODE tempnode = new Node();
		tempnode->loadInfoFromString(gridInfoLines[i]);
		cells.push_back(tempnode);
	}
	std::vector<std::string> objsInfoLines = getAllLineInTextFile(STAGE3_1_OBJS_FILE);
	for (int i = 0; i < objsInfoLines.size(); i++)
	{
		int id, kind, posx, posy, width, height;
		findAndReplaceAll(objsInfoLines[i], ",", " ");
		std::stringstream iss(objsInfoLines[i]);
		iss >> id;
		iss >> kind;
		iss >> posx;
		iss >> posy;
		iss >> width;
		iss >> height;
		objIDs.push_back(id);
		switch (id)
		{
		case 0:
			break;
		default:
			break;
		}
	}
}

void Grid::updateAfterDeltaTime(float deltaT)
{
	for (int i = 0; i < objIDs.size(); i++)
		isUpdatedObjs[objIDs[i]] = false;

	for (int i = 0; i < cells.size(); i++)
		cells[i]->updateAfterDeltaTime(deltaT, this);
	
}

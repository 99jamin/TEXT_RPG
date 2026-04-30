#pragma once
#include <iostream>
#include "../map/Map.h"

class UIRenderer
{

public:

	static void printMiniMap(const Map& map)
	{
		int curX = map.getCurrentX();
		int curY = map.getCurrentY();
		auto& gird = map.getRoomGrid();

		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 6; ++x)
			{
				if (!gird[y][x])
				{
					std::cout << "  ";
				}
				else if(x==curX && y==curY)
				{
					std::cout << "■";
				}
				else
				{
					std::cout << "□";
				}
			}
			std::cout << "\n";
		}
	}

private:



};

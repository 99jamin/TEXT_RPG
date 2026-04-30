#pragma once
#include <string>

enum class Direction
{ 
	North, 
	South, 
	East, 
	West 
};

inline std::string dirToString(Direction dir)
{
    switch (dir)
    {
    case Direction::North: return "북쪽";
    case Direction::South: return "남쪽";
    case Direction::West: return "서쪽";
    case Direction::East: return "동쪽";
    default: return "알 수 없음";
    }
}

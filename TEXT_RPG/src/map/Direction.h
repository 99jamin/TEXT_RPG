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
    case Direction::North: return "↑";
    case Direction::South: return "↓";
    case Direction::West: return "←";
    case Direction::East: return "→";
    default: return "알 수 없음";
    }
}

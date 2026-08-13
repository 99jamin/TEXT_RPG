#pragma once
#define NOMINMAX
#include <vector>
#include <string>
#include <windows.h>

enum class Color : WORD
{
	WHITE = 7,
	RED = 12,
	GREEN = 10,
	YELLOW = 14,
	CYAN = 11,
	PURPLE = 13,
	ORANGE = 6,
	BLUE = 9,
	BOSS = 5,
	BWHITE = 15,

};

struct LogSegment
{
	std::string text;
	Color color;

	LogSegment(const std::string& t, Color c) : text(t), color(c) {}
};

using LogLine = std::vector<LogSegment>;
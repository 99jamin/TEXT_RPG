#pragma once
#include <string>
#include <vector>
#include <functional>
#include "../ui/LogLine.h"

class Player;
class Monster;

class PlayerCommand
{
public:

	virtual void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) = 0;

};
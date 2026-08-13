#pragma once
#include <string>
#include <vector>
#include <functional>
#include "../ui/LogLine.h"

class Monster;
class Player;

class MonsterCommand
{
public:

	virtual void execute(Monster& monster, Player& player, std::function<void(LogLine)> logCallback = nullptr) = 0;

protected:

	LogLine m_log;
};
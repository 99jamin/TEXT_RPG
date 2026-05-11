#pragma once
#include "PlayerCommand.h"
#include "../entity/Player.h"

class DefendCommand : public PlayerCommand
{

public:

	void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		player.startDefend();
		
		if (logCallback)
		{
			m_log.clear();
			m_log.push_back(LogSegment("방어 자세를 취했다.", Color::WHITE));
			logCallback(m_log);
		}

		return;
	}

};

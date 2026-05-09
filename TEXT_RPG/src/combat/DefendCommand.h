#pragma once
#include "Command.h"
#include "../entity/Player.h"

class DefendCommand : public Command
{

public:

	void execute(Entity& user, std::vector<Entity*>& targets, int targetIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		Player* player = dynamic_cast<Player*>(&user);
		if (!player) return;

		player->startDefend();
		
		
		if (logCallback)
		{
			m_log.clear();
			m_log.push_back(LogSegment("방어 자세를 취했다.", Color::WHITE));
			logCallback(m_log);
		}

		return;
	}

};

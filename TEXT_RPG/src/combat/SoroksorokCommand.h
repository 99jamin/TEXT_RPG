#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"
#include "../entity/Boss.h"

class SoroksorokCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		player.consumeStamina(m_staminaCost);


		if (monsters[monsterIndex]->isBoss())
		{
			if (logCallback)
			{
				m_log.clear();
				m_log.push_back(LogSegment("<" + m_name + ">", Color::CYAN));
				m_log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));
				m_log.push_back(LogSegment("[" + monsters[monsterIndex]->getName() + "]", Color::BOSS));
				m_log.push_back(LogSegment(" 는 울음을 그치고 안식에 들었다.", Color::WHITE));
				logCallback(m_log);
			}

			monsters[monsterIndex]-> dead();
		}
		else
		{
			if (logCallback)
			{
				m_log.clear();
				m_log.push_back(LogSegment("<" + m_name + ">", Color::CYAN));
				m_log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));
				m_log.push_back(LogSegment(" 아무런 효과가 없다...", Color::WHITE));
				logCallback(m_log);
			}
		}

		return;
	}

private:
	LogLine m_log;
};
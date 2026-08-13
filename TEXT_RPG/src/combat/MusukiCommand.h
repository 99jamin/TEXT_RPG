#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class MusukiCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		player.consumeStamina(m_staminaCost);

		int realDamage = 0;

		int actualDamage = static_cast<int>(player.getAtk() * m_damageRatio);

		realDamage = monsters[monsterIndex]->takeDamage(actualDamage);
		monsters[monsterIndex]->takeDamage(actualDamage);

		if (logCallback)
		{
			m_log.clear();
			m_log.push_back(LogSegment("<" + m_name + ">", Color::BLUE));
			m_log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));
			m_log.push_back(LogSegment("[" + monsters[monsterIndex]->getName() + "]", Color::RED));
			m_log.push_back(LogSegment(" 에게 ", Color::WHITE));
			m_log.push_back(LogSegment(std::to_string(realDamage), Color::ORANGE));
			m_log.push_back(LogSegment(" 의 피해를 두번 입혔다.", Color::WHITE));
			logCallback(m_log);
		}

		return;
	}

private:
	LogLine m_log;
};

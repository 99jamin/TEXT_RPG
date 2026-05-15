#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"
#include "../entity/Player.h"

class GumniCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{

		int realDamage = 0;

		if (!player.isConcentrating())
		{
			player.consumeStamina(m_staminaCost);

			player.startConcentrate();

			m_log.clear();
			m_log.push_back(LogSegment("<" + m_name + ">", Color::BLUE));
			m_log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));

			m_log.push_back(LogSegment("적에게 ", Color::WHITE));
			m_log.push_back(LogSegment("[집중]", Color::YELLOW));
			m_log.push_back(LogSegment(" 하고있다.", Color::WHITE));
		}
		else
		{
			if (player.wasHitWhileConcentrating())
			{
				int actualdamage = player.getAtk() * HIT_DAMAGE_RATIO;
				realDamage = monsters[monsterIndex]->takeDamage(actualdamage);
			}
			else
			{
				int actualdamage = (player.getAtk() * m_damageRatio);
				realDamage = monsters[monsterIndex]->takeDamage(actualdamage);
			}

			m_log.clear();
			m_log.push_back(LogSegment("[집중]", Color::YELLOW));
			m_log.push_back(LogSegment(" 을 끝냈다, ", Color::WHITE));
			m_log.push_back(LogSegment("[" + monsters[monsterIndex]->getName() + "]", Color::RED));
			m_log.push_back(LogSegment(" 에게 ", Color::WHITE));
			m_log.push_back(LogSegment(std::to_string(realDamage), Color::ORANGE));
			m_log.push_back(LogSegment(" 의 피해를 입혔다.", Color::WHITE));

			player.endConcentrate();
		}

		if (logCallback)
			logCallback(m_log);

		return;
	}

private:

	LogLine m_log;
	static constexpr float HIT_DAMAGE_RATIO = 3.0f;
};

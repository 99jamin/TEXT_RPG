#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class MulmaruCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Entity& user, std::vector<Entity*>& targets, int targetIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		Player* player = dynamic_cast<Player*>(&user);
		if (player) player->consumeStamina(m_staminaCost);

		int realDamage = 0;

		int actualDamage = user.getAtk() * m_damageRatio;

		realDamage = targets[targetIndex]->takeDamage(actualDamage);

		if (logCallback)
		{
			m_log.clear();
			m_log.push_back(LogSegment("<" + m_name + ">", Color::BLUE));
			m_log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));
			m_log.push_back(LogSegment("[" + targets[targetIndex]->getName() + "]", Color::RED));
			m_log.push_back(LogSegment(" 에게 ", Color::WHITE));
			m_log.push_back(LogSegment(std::to_string(realDamage), Color::ORANGE));
			m_log.push_back(LogSegment(" 의 피해를 입혔다.", Color::WHITE));
			logCallback(m_log);
		}

		return;
	}

};
#pragma once
#include "Command.h"
#include "../data/DataTypes.h"
#include <string>


class SkillCommand : public Command
{

public:

	SkillCommand(const SkillData& data)
		:m_name(data.name), m_damageRatio(data.damage_ratio), m_staminaCost(data.stamina_cost)
	{

	}

	virtual void execute(Entity& user, std::vector<Entity*>& targets, int targetIndex, std::function<void(LogLine)> logCallback = nullptr) = 0;

	
protected:

	float m_damageRatio;
	int m_staminaCost;
	std::string m_name;
	LogLine m_log;
};

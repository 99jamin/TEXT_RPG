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

	virtual int execute(Entity& user, Entity& target) = 0;
	

	std::string getDescription() const override
	{
		return m_name;
	}

	int getStaminaCost() const override
	{
		return m_staminaCost;
	}


protected:

	float m_damageRatio;
	int m_staminaCost;
	std::string m_name;

};

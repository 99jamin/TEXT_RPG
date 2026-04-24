#pragma once
#include "Command.h"

class SkillCommand : public Command
{

public:

	SkillCommand(const std::string& name, float damageRatio, int staminaCost)
		:m_name(name), m_damageRatio(damageRatio), m_staminaCost(staminaCost)
	{

	}

	virtual void execute(Entity& user, Entity& target) = 0;
	

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

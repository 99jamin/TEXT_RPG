#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class MusukiCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Entity& user, Entity& target) override
	{
		int actualDamage = user.getAtk() * m_damageRatio;

		target.takeDamage(actualDamage);
		target.takeDamage(actualDamage);
	}

};

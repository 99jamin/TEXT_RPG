#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class NeoulCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	int execute(Entity& user, Entity& target) override
	{
		int realDamage = 0;
		int actualDamage = user.getAtk() * m_damageRatio;

		realDamage = target.takeDamage(actualDamage);

		return realDamage;
	}

};

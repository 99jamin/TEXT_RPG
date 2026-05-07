#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class MulmaruCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	int execute(Entity& user, Entity& target) override
	{
		int realDmamage = 0;
		int actualDamage = user.getAtk() * m_damageRatio;

		realDmamage = target.takeDamage(actualDamage);

		return realDmamage;
	}

};
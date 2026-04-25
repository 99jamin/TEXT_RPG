#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"

class NuigyeolCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Entity& user, Entity& target) override
	{
		int actualDamage = user.getAtk()* m_damageRatio;

		target.takeDamage(actualDamage);
	}

};
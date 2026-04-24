#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"
#include "../entity/Boss.h"

class SoroksorokCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Entity& user, Entity& target) override
	{
		Boss* boss = dynamic_cast<Boss*>(&target);
		if (boss) {
			target.dead();
		}
	}

};
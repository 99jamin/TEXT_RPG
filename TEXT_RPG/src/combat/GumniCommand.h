#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"
#include "../entity/Player.h"

class GumniCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	void execute(Entity& user, Entity& target) override
	{
		Player* player = dynamic_cast<Player*>(&user);
		if (!player) return;

		if (!player->isChargingGumni())
		{
			player->startGumniCharge();
		}
		else
		{
			if (player->wasHitWhileCharging())
			{
				int actualdamage = player->getAtk() * HIT_DAMAGE_RATIO;
				target.takeDamage(actualdamage);
			}
			else
			{
				int actualdamage = (player->getAtk() * m_damageRatio);
				target.takeDamage(actualdamage);
			}

			player->releaseGumni();
		}
	}

private:

	static constexpr float HIT_DAMAGE_RATIO = 2.0f;
};

#pragma once
#include "SkillCommand.h"
#include "../entity/Entity.h"
#include "../entity/Player.h"

class GumniCommand : public SkillCommand
{
public:

	using SkillCommand::SkillCommand;

	int execute(Entity& user, Entity& target) override
	{
		int realDamage = 0;

		Player* player = dynamic_cast<Player*>(&user);
		if (!player) return 0;

		if (!player->isChargingGumni())
		{
			player->startGumniCharge();
		}
		else
		{
			if (player->wasHitWhileCharging())
			{
				int actualdamage = player->getAtk() * HIT_DAMAGE_RATIO;
				realDamage = target.takeDamage(actualdamage);
			}
			else
			{
				int actualdamage = (player->getAtk() * m_damageRatio);
				realDamage = target.takeDamage(actualdamage);
			}

			player->releaseGumni();
		}

		return realDamage;
	}

private:

	static constexpr float HIT_DAMAGE_RATIO = 2.0f;
};

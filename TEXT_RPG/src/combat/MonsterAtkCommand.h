#pragma once
#include "Command.h"
#include "../entity/Monster.h"
#include "../entity/Player.h"

class MonsterAtkCommand : public Command
{

public:

	int execute(Entity& user, Entity& target) override
	{
		Monster* monster = dynamic_cast<Monster*>(&user);
		if (!monster) return 0;

        Player* player = dynamic_cast<Player*>(&target);
        if (!player) return 0;

        int actualDamage = 0;

        int realDamage = 0;

        switch (monster->getEffect()) {
        case MonsterEffect::None:
            
            actualDamage = static_cast<int>(monster->getAtk() * DAMAGE_RATIO);
            realDamage = player->takeDamage(actualDamage);
            break;

        case MonsterEffect::Poison:
            
            actualDamage = static_cast<int>(monster->getAtk() * DAMAGE_RATIO);
            realDamage = player->takeDamage(actualDamage);
            player->applyPoison();
            break;

        case MonsterEffect::StaminaDrain:
            
            actualDamage = static_cast<int>(monster->getAtk() * DAMAGE_RATIO);
            realDamage = player->takeDamage(actualDamage);
            player->drainStamina(1);
            break;

        case MonsterEffect::HighDamage:
            
            actualDamage = static_cast<int>(monster->getAtk() * HIGH_DAMAGE_RATIO);
            realDamage = player->takeDamage(actualDamage);
            break;

        case MonsterEffect::HpAbsorb:
            
            actualDamage = static_cast<int>(monster->getAtk() * DAMAGE_RATIO);
            realDamage = player->takeDamage(actualDamage);
            monster->recoverHp(actualDamage * HP_ABSORB_RATIO);
            break;

        case MonsterEffect::HpRegen:
            
            monster->recoverHp(static_cast<int>(actualDamage * HP_ABSORB_RATIO));
            break;
        }

        return realDamage;
	}


	std::string getDescription() const override
	{
        return "적이 공격한다.";
	}


private:

    static constexpr float DAMAGE_RATIO = 1.2;
    static constexpr float HIGH_DAMAGE_RATIO = 2.0;
    static constexpr float HP_ABSORB_RATIO = 0.2;
    static constexpr int HP_REGEN_RATIO = 3;

};

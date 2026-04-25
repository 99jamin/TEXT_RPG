#pragma once
#include "Command.h"
#include "../entity/Monster.h"
#include "../entity/Player.h"

class MonsterAtkCommand : public Command
{

public:

	void execute(Entity& user, Entity& target) override
	{
		Monster* monster = dynamic_cast<Monster*>(&user);
		if (!monster) return;

        Player* player = dynamic_cast<Player*>(&target);
        if (!player) return;

        int actualDamage = 0;

        switch (monster->getEffect()) {
        case MonsterEffect::None:
            // 일반 공격
            actualDamage = monster->getAtk()* DAMAGE_RATIO;
            player->takeDamage(actualDamage);
            break;

        case MonsterEffect::Poison:
            // 독 부여
            actualDamage = monster->getAtk() * DAMAGE_RATIO;
            player->takeDamage(actualDamage);
            player->applyPoison();
            break;

        case MonsterEffect::StaminaDrain:
            // 기력 감소
            actualDamage = monster->getAtk() * DAMAGE_RATIO;
            player->takeDamage(actualDamage);
            player->drainStamina(1);
            break;

        case MonsterEffect::HighDamage:
            //데미지 뻥튀기
            actualDamage = monster->getAtk() * HIGH_DAMAGE_RATIO;
            player->takeDamage(actualDamage);
            break;

        case MonsterEffect::HpAbsorb:
            //Hp 흡수
            actualDamage = monster->getAtk() * DAMAGE_RATIO;
            player->takeDamage(actualDamage);
            monster->recoverHp(actualDamage * HP_ABSORB_RATIO);
            break;

        case MonsterEffect::HpRegen:
            //Hp 리젠, 데미지는 0
            monster->recoverHp((monster->getMaxHp())/ HP_REGEN_RATIO);
            break;
        }
	}


	std::string getDescription() const override
	{
        return "적의 공격";
	}


private:

    static constexpr float DAMAGE_RATIO = 1.2;
    static constexpr float HIGH_DAMAGE_RATIO = 2.0;
    static constexpr float HP_ABSORB_RATIO = 0.2;
    static constexpr int HP_REGEN_RATIO = 3;

};

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
            actualDamage = monster->getAtk()* m_damageRatio;
            player->takeDamage(actualDamage);
            break;

        case MonsterEffect::Poison:
            // 독 부여
            break;

        case MonsterEffect::StaminaDrain:
            // 기력 감소
            break;

        case MonsterEffect::HighDamage:
            //데미지 뻥튀기
            actualDamage = monster->getAtk() * m_damageRatio;
            player->takeDamage(actualDamage);
            break;

        case MonsterEffect::HpAbsorb:
            //Hp 흡수
            actualDamage = monster->getAtk() * m_damageRatio;
            player->takeDamage(actualDamage);
            monster->recoverHp(actualDamage * 0.2);
            break;

        case MonsterEffect::HpRegen:
            //Hp 리젠, 데미지는 0
            monster->recoverHp((monster->getMaxHp())/3);
            break;
        }
	}


	std::string getDescription() const override
	{
        return name;
	}


private:

    std::string name = "monster";
    float m_damageRatio;

};

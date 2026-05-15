#pragma once
#include "MonsterCommand.h"
#include "../entity/Monster.h"
#include "../entity/Player.h"

class MonsterAtkCommand : public MonsterCommand
{

public:

    void execute(Monster& monster, Player& player, std::function<void(LogLine)> logCallback = nullptr) override
	{
        int actualDamage = 0;

        int realDamage = 0;

        switch (monster.getEffect()) {
        case MonsterEffect::None:
            
            actualDamage = static_cast<int>(monster.getAtk() * DAMAGE_RATIO);
            realDamage = player.takeDamage(actualDamage);
            break;

        case MonsterEffect::Poison:
            
            actualDamage = static_cast<int>(monster.getAtk() * DAMAGE_RATIO);
            realDamage = player.takeDamage(actualDamage);
            player.applyPoison();
            break;

        case MonsterEffect::StaminaDrain:
            
            actualDamage = static_cast<int>(monster.getAtk() * DAMAGE_RATIO);
            realDamage = player.takeDamage(actualDamage);
            player.drainStamina(1);
            break;

        case MonsterEffect::HighDamage:
            
            actualDamage = static_cast<int>(monster.getAtk() * HIGH_DAMAGE_RATIO);
            realDamage = player.takeDamage(actualDamage);
            break;

        case MonsterEffect::HpAbsorb:
            
            actualDamage = static_cast<int>(monster.getAtk() * DAMAGE_RATIO);
            realDamage = player.takeDamage(actualDamage);
            monster.recoverHp(actualDamage * HP_ABSORB_RATIO);
            break;

        case MonsterEffect::HpRegen:
            
            monster.recoverHp(static_cast<int>(actualDamage * HP_ABSORB_RATIO));
            break;
        }

        if (logCallback)
        {
            m_log.clear();
            m_log.push_back(LogSegment("[" + monster.getName() + "]", Color::RED));
            m_log.push_back(LogSegment(monster.getAttackLog(), Color::WHITE));
            m_log.push_back(LogSegment(" " + std::to_string(realDamage), Color::RED));
            m_log.push_back(LogSegment(" 의 피해를 입었다.", Color::WHITE));
            logCallback(m_log);
        }

        return;
	}


private:
    static constexpr float DAMAGE_RATIO = 1.2;
    static constexpr float HIGH_DAMAGE_RATIO = 2.0;
    static constexpr float HP_ABSORB_RATIO = 0.2;
    static constexpr int HP_REGEN_RATIO = 3;
};

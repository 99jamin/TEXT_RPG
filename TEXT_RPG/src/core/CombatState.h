#pragma once
#include <vector>
#include <string>
#include <functional>
#include "GameState.h"
#include "../combat/CombatSystem.h"
#include "../combat/CombatResult.h"
#include "GameManager.h"
#include "../entity/JeokgapsinBoss.h"
#include "../entity/JeokkwiBoss.h"

class GameManager;

class CombatState : public GameState
{
public:

	CombatState(int monsterCount, std::string monsterId, std::function<void(CombatResult)> onResult)
		: m_onResult(onResult)
	{
		MonsterData data = DataManager::getInstance().getMonsterData(monsterId);

		if (monsterId == "jeokgapsin")
		{
			m_monsters.push_back(std::make_unique<JeokgapsinBoss>(data));
		}
		else if (monsterId == "jeokkwi")
		{
			m_monsters.push_back(std::make_unique<JeokkwiBoss>(data));
		}
		else
		{
			for (int i = 0; i < monsterCount; i++)
			{
				m_monsters.push_back(std::make_unique<Monster>(data));
			}
		}
	}

	void enter(GameManager& manager) override
	{
		std::vector<Monster*> rawPtrs;
		for (auto& m : m_monsters)
			rawPtrs.push_back(m.get());
		m_combatSystem = std::make_unique<CombatSystem>(manager.getPlayer(), rawPtrs);
	}

	void update(GameManager& manager) override
	{
		CombatResult result = m_combatSystem->combatStart();
		switch (result)
		{
		case CombatResult::Victory:
		{
			m_onResult(CombatResult::Victory);
			manager.popState();
			break;
		}
		case CombatResult::Defeat:
		{
			m_onResult(CombatResult::Defeat);
			manager.gameover();
			break;
		}
		case CombatResult::Fled:
		{
			m_onResult(CombatResult::Fled);
			manager.popState();
			break;
		}
		}
	}

	void exit(GameManager& manager) override
	{

	}

private:
	std::function<void(CombatResult)> m_onResult;
	std::vector<std::unique_ptr<Monster>> m_monsters;
	std::unique_ptr<CombatSystem> m_combatSystem;
};


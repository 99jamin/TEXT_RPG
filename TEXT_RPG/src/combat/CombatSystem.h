#pragma once
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "CombatResult.h"
#include "DefendCommand.h"
#include "FleeCommand.h"
#include "MonsterAtkCommand.h"
#include "SkillCommandFactory.h"
#include "../ui/UIRenderer.h"
#include <iostream>

class CombatSystem
{

public:

	CombatSystem(Player& player, std::vector<Monster*>monsters)
		:m_player(player),m_monsters(monsters)
	{
		m_isRunning = true;
	}

	CombatResult combatStart()
	{
		while (m_isRunning)
		{
			playerTurn();

			if (!m_isRunning) break;

			for (auto& e : m_monsters)
			{
				monsterTurn(*e);
			}
		}

		return m_result;
	}

	
	void playerTurn()
	{
		m_player.recoverStamina(1);  

		if (m_player.isChargingGumni())
		{
			UIRenderer::addLog("집중을 끝냈다.");
			auto cmd = createSkillCommand(SkillType::Gumni);
			cmd->execute(m_player, *m_monsters[0]);
			checkMonsters();
			return;
		}

		if (m_player.isPoisoned())
		{
			UIRenderer::addLog("역병에 걸려 피해를 입고있다.");
			m_player.takeDamage(POISON_DAMAGE);
		}


		if (!m_player.isAlive())
		{
			m_result = CombatResult::Defeat;
			combatEnd();
			return;
		}

		std::vector<std::string> choice = { "1. 공격","2. 방어","3. 도주","4. 소지품", };
		UIRenderer::printCombatScreen(m_monsters, m_player, choice);
		
		
		int input;
		std::cin >> input;

		switch (input)
		{


		case 1:
		{
			std::vector<std::string> skillChoice;

			int count = 0;
			std::vector<SkillType> skills = m_player.getSkills();
			for (auto& e : skills)		
			{
				skillChoice.push_back(std::to_string(++count)+ "."+ toString(e));
			}

			UIRenderer::printCombatScreen(m_monsters, m_player, skillChoice);

			std::cin >> input;
			SkillType selected = skills[input - 1];
			auto skill = createSkillCommand(selected);
			skill->execute(m_player, *m_monsters[0]);
			UIRenderer::addLog(skill->getDescription() + " 을 사용했다.");
			m_player.consumeStamina(skill->getStaminaCost());

			checkMonsters();

			break;
		}

		case 2:
		{
			DefendCommand().execute(m_player, *m_monsters[0]);
			UIRenderer::addLog("방어 자세를 잡았다.");
			break;
		}
			
		case 3:
		{
			FleeCommand fleecommand;
			fleecommand.execute(m_player, *m_monsters[0]);
			UIRenderer::addLog(fleecommand.getDescription());

			if (fleecommand.isFleeSuccess())
			{
				m_result = CombatResult::Fled;
				combatEnd();
			}
			break;
		}
			

		case 4:
		{
			//Item
			break;
		}

		}
	}

	void monsterTurn(Monster& monster)
	{
		MonsterAtkCommand().execute(monster, m_player);
		
		UIRenderer::addLog(monster.getName()+" 의 공격");

		m_player.endDefend();

		if (!m_player.isAlive())
		{
			m_result = CombatResult::Defeat;
			combatEnd();
		}
	}

	void combatEnd()
	{
		m_isRunning = false;
	}


private:

	Player& m_player;
	std::vector<Monster*> m_monsters;
	bool m_isRunning = true;

	CombatResult m_result = CombatResult::Victory;

	static constexpr int POISON_DAMAGE = 5;

	void checkMonsters()
	{
		m_monsters.erase(
			std::remove_if(m_monsters.begin(), m_monsters.end(),
				[](Monster* m) { return !m->isAlive(); }),
			m_monsters.end()
		);

		if (m_monsters.empty())
		{
			m_result = CombatResult::Victory;
			combatEnd();
		}
	}
};

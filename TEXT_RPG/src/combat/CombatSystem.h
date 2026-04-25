#pragma once
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "CombatResult.h"
#include "DefendCommand.h"
#include "FleeCommand.h"
#include "MonsterAtkCommand.h"
#include "SkillCommandFactory.h"
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

		m_player.recoverStamina(1);  // 추가

		// 독 데미지 먼저 처리
		if (m_player.isPoisoned())
			m_player.takeDamage(POISON_DAMAGE);

		if (!m_player.isAlive())
		{
			m_result = CombatResult::Defeat;
			combatEnd();
			return;
		}

		int input;
		std::cout << "1.공격하기\n2.방어하기\n3.도망가기\n4.아이템";
		std::cin >> input;

		switch (input)
		{

			

		case 1:
		{
			int count = 0;
			std::vector<SkillType> skills = m_player.getSkills();
			for (auto& e : skills)
			{
				std::cout << ++count << "." << toString(e) << std::endl;
			}

			std::cin >> input;
			SkillType selected = skills[input - 1];
			auto skill = createSkillCommand(selected);
			skill->execute(m_player, *m_monsters[0]);

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

			break;
		}

		case 2:
		{
			DefendCommand().execute(m_player, *m_monsters[0]);
			break;
		}
			
		case 3:
		{
			FleeCommand fleecommand;
			fleecommand.execute(m_player, *m_monsters[0]);
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

	//전투 결과
	CombatResult m_result = CombatResult::Victory;

	//상태이상
	static constexpr int POISON_DAMAGE = 5;
};

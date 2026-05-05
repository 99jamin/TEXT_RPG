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
			auto skill = createSkillCommand(SkillType::Gumni);

			if (m_monsters.size() == 1)
			{
				skill->execute(m_player, *m_monsters[0]);
			}
			else
			{
				printTargetChoice();
				int targetInput;
				std::cin >> targetInput;
				if (targetInput <= m_monsters.size() && targetInput > 0)
					skill->execute(m_player, *m_monsters[targetInput - 1]);
				else
				{
					UIRenderer::addLog("잘못된 선택입니다.");
					return;
				}
			}
			
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

			int skillInput;
			std::cin >> skillInput;
			SkillType selected = skills[skillInput - 1];
			auto skill = createSkillCommand(selected);

			if (selected == SkillType::Neoul)
			{
				UIRenderer::addLog(skill->getDescription() + " 을 사용했다.");
				for (auto& e : m_monsters)
				{
					skill->execute(m_player, *e);
				}
			}
			else if (selected == SkillType::Gumni)
			{
				UIRenderer::addLog(skill->getDescription() + " 을 사용했다.");
				skill->execute(m_player, *m_monsters[0]);	//굼니 커맨드의 첫번째 호출은 어떤 몬스터 포인터든 상관없음.
			}
			else
			{
				if (m_monsters.size() == 1)
				{
					UIRenderer::addLog(skill->getDescription() + " 을 사용했다.");
					skill->execute(m_player, *m_monsters[0]);
				}
				else
				{
					printTargetChoice();
					int targetInput;
					std::cin >> targetInput;
					

					if (targetInput <= m_monsters.size() && targetInput > 0)
					{
						UIRenderer::addLog(skill->getDescription() + " 을 사용했다.");
						skill->execute(m_player, *m_monsters[targetInput - 1]);
					}
					else
					{
						UIRenderer::addLog("잘못된 선택입니다.");
						return;
					}
				}
			}

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
			handleItemInCombat();
			break;
		}
		}
	}

	void monsterTurn(Monster& monster)
	{
		UIRenderer::addLog(monster.getName() + " 의 공격");

		MonsterAtkCommand().execute(monster, m_player);
		
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

	void printTargetChoice()
	{
		std::vector<std::string> choice;
		int count = 0;
		for (auto& e : m_monsters)
		{
			if (e->isAlive())
				choice.push_back(std::to_string(++count) + ". " + e->getName());
		}

		UIRenderer::printCombatScreen(m_monsters, m_player, choice);
	}

	void handleItemInCombat()
	{
		auto& inven = m_player.getInven();

		if (inven.empty())
		{
			UIRenderer::addLog("소지품이 없다.");
			return;
		}

		// 아이템 목록 출력
		std::vector<std::string> itemChoices;
		std::vector<std::pair<std::string, int>> itemList;
		int count = 0;
		for (auto& e : inven)
		{
			itemList.push_back(e);
			ItemData data = DataManager::getInstance().getItemData(e.first);
			itemChoices.push_back(std::to_string(++count) + ". " + data.name);
		}
		itemChoices.push_back(std::to_string(++count) + ". 취소");

		UIRenderer::printInvenScreen(itemList, m_player, itemChoices);

		int input;
		std::cin >> input;

		if (input == count) return; // 취소
		if (input < 1 || input >= count)
		{
			UIRenderer::addLog("잘못된 선택입니다.");
			return;
		}

		std::string selectedId = itemList[input - 1].first;
		m_player.useItem(selectedId);
	}

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

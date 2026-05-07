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
			std::vector<LogSegment>dmgLog;

			dmgLog.push_back(LogSegment("[집중]", Color::YELLOW));
			dmgLog.push_back(LogSegment(" 을 끝냈다, ", Color::WHITE));
			dmgLog.push_back(LogSegment("[" + m_monsters[0]->getName() + "]", Color::RED));
			dmgLog.push_back(LogSegment(" 에게 ", Color::WHITE));

			int actualDamage = 0;

			auto skill = createSkillCommand(SkillType::Gumni);


			if (m_monsters.size() == 1)
			{
				actualDamage = skill->execute(m_player, *m_monsters[0]);
				dmgLog.push_back(LogSegment(std::to_string(actualDamage), Color::ORANGE));
				dmgLog.push_back(LogSegment(" 의 피해를 입혔다.", Color::WHITE));
				UIRenderer::addLog(dmgLog);
			}
			else
			{
				printTargetChoice();
				int targetInput;
				std::cin >> targetInput;
				if (targetInput <= m_monsters.size() && targetInput > 0)
				{
					actualDamage = skill->execute(m_player, *m_monsters[targetInput - 1]);
					dmgLog.push_back(LogSegment(std::to_string(actualDamage), Color::ORANGE));
					dmgLog.push_back(LogSegment(" 의 피해를 입혔다.", Color::WHITE));
					UIRenderer::addLog(dmgLog);
				}
				else
				{
					//UIRenderer::addLog("잘못된 선택입니다.");
					return;
				}
			}
			
			checkMonsters();
			return;
		}

		if (m_player.isPoisoned())
		{
			int damage = m_player.takeDamage(POISON_DAMAGE);

			std::vector<LogSegment>log;
			log.push_back(LogSegment("[역병]", Color::PURPLE));
			log.push_back(LogSegment("에 의해 ", Color::WHITE));
			log.push_back(LogSegment(std::to_string(damage), Color::PURPLE));
			log.push_back(LogSegment(" 의 피해를 입었다.", Color::WHITE));
			UIRenderer::addLog(log);
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

			if (skills.empty())
			{
				UIRenderer::addLog("공격할 수단이 없다. 무가서를 읽어야 한다.");
				return;
			}

			for (auto& e : skills)		
			{
				skillChoice.push_back(std::to_string(++count)+ "."+ toString(e));
			}

			UIRenderer::printCombatScreen(m_monsters, m_player, skillChoice);

			int skillInput;
			std::cin >> skillInput;
			SkillType selected = skills[skillInput - 1];
			auto skill = createSkillCommand(selected);

			std::vector<LogSegment>log;
			int actualDamage = 0;
			
			if (selected == SkillType::Neoul)
			{
				log.push_back(LogSegment("<" + skill->getDescription() + ">", Color::BLUE));
				log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));

				log.push_back(LogSegment("[적 전체]", Color::RED));
				log.push_back(LogSegment(" 에게", Color::WHITE));

				for (auto& e : m_monsters)
				{
					actualDamage = skill->execute(m_player, *e);
				}

				log.push_back(LogSegment(std::to_string(actualDamage), Color::ORANGE));

			}
			else if (selected == SkillType::Gumni)
			{
				log.push_back(LogSegment("<" + skill->getDescription() + ">", Color::BLUE));
				log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));

				log.push_back(LogSegment("적에게 ", Color::WHITE));
				log.push_back(LogSegment("[집중]", Color::YELLOW));
				log.push_back(LogSegment(" 하고있다.", Color::WHITE));

				skill->execute(m_player, *m_monsters[0]);	//굼니 커맨드의 첫번째 호출은 어떤 몬스터 포인터든 상관없음.
			}
			else
			{
				if (m_monsters.size() == 1)
				{
					log.push_back(LogSegment("<" + skill->getDescription() + ">", Color::BLUE));
					log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));

					log.push_back(LogSegment("[" + m_monsters[0]->getName() + "]", Color::RED));
					log.push_back(LogSegment(" 에게", Color::WHITE));

					actualDamage = skill->execute(m_player, *m_monsters[0]);

					log.push_back(LogSegment(std::to_string(actualDamage), Color::ORANGE));
				}
				else
				{
					printTargetChoice();
					int targetInput;
					std::cin >> targetInput;
					

					if (targetInput <= m_monsters.size() && targetInput > 0)
					{
						log.push_back(LogSegment("<" + skill->getDescription() + ">", Color::BLUE));
						log.push_back(LogSegment(" 을/를 사용했다, ", Color::WHITE));

						log.push_back(LogSegment("[" + m_monsters[0]->getName() + "]", Color::RED));
						log.push_back(LogSegment(" 에게", Color::WHITE));

						actualDamage = skill->execute(m_player, *m_monsters[targetInput - 1]);

						log.push_back(LogSegment(std::to_string(actualDamage), Color::ORANGE));

					}
					else
					{
						//UIRenderer::addLog("잘못된 선택입니다.");
						return;
					}
				}
			}

			if (selected != SkillType::Gumni)
				log.push_back(LogSegment(" 의 피해를 입혔다.", Color::WHITE));

			UIRenderer::addLog(log);
			

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
		int damage = MonsterAtkCommand().execute(monster, m_player);

		std::vector<LogSegment> dmgLog;
		dmgLog.push_back(LogSegment("[" + monster.getName() + "]", Color::RED));
		dmgLog.push_back(LogSegment(" 의 공격, ", Color::WHITE));
		dmgLog.push_back(LogSegment(" "+std::to_string(damage), Color::RED));
		dmgLog.push_back(LogSegment(" 의 피해를 입었다.", Color::WHITE));
		UIRenderer::addLog(dmgLog);
		
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

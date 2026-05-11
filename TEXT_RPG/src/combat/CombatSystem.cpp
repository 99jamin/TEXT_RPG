#include "CombatSystem.h"
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "DefendCommand.h"
#include "FleeCommand.h"
#include "MonsterAtkCommand.h"
#include "SkillCommandFactory.h"
#include "../ui/UIRenderer.h"
#include "../input/InputHandler.h"
#include <iostream>

CombatSystem::CombatSystem(Player& player, std::vector<Monster*> monsters)
	:m_player(player), m_monsters(monsters)
{
	m_isRunning = true;
}

CombatResult CombatSystem::combatStart()
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

void CombatSystem::playerTurn()
{
	//플레이어 스태미너 회복
	m_player.recoverStamina(1);


	//플레이어 상태 체크
	if (!checkPlayerStatus())
		return;


	//플레이어 입력
	std::vector<std::string> choice = { "1. 공격","2. 방어","3. 도주","4. 소지품", };
	bool actionDone = false;
	while (!actionDone)

	{
		UIRenderer::printCombatScreen(m_monsters, m_player, choice);

		int input = InputHandler::getInt(1, 4, [&]() {UIRenderer::printCombatScreen(m_monsters, m_player, choice); });

		switch (input)
		{
		case 1:
		{
			actionDone = executeSkillCommand();
			break;
		}

		case 2:
		{
			actionDone = executeDefendCommand();
			break;
		}

		case 3:
		{
			actionDone = executeFleeCommand();
			break;
		}

		case 4:
		{
			actionDone = handleItemInCombat();
			break;
		}
		}
	}
}

void CombatSystem::monsterTurn(Monster& monster)
{

	MonsterAtkCommand().execute(monster, m_player, [](LogLine log) {UIRenderer::addLog(log); });

	if (!m_player.isAlive())
	{
		m_result = CombatResult::Defeat;
		combatEnd();
	}
}

void CombatSystem::combatEnd()
{
	m_isRunning = false;
}

void CombatSystem::printTargetChoice()
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

bool CombatSystem::checkPlayerStatus()
{

	//카운터 스킬 상태 체크
	if (m_player.isConcentrating())
	{
		auto skill = createSkillCommand(SkillType::Gumni);

		if (m_monsters.size() == 1)
		{
			skill->execute(m_player, m_monsters, 0, [](LogLine log) {UIRenderer::addLog(log); });
		}
		else
		{
			printTargetChoice();

			int targetInput = InputHandler::getInt(1, m_monsters.size(), [&]() {printTargetChoice(); }) - 1;

			skill->execute(m_player, m_monsters, targetInput, [](LogLine log) {UIRenderer::addLog(log); });
		}

		checkMonsters();
		return false;
	}

	//플레이어 상태이상 체크
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

	//플레이어 생존 체크
	if (!m_player.isAlive())
	{
		m_result = CombatResult::Defeat;
		combatEnd();
		return false;
	}

	return true;
}

bool CombatSystem::executeSkillCommand()
{
	//스킬 선택
	std::vector<std::string> skillChoice;

	int count = 0;
	std::vector<SkillType> skills = m_player.getSkills();

	if (skills.empty())
	{
		UIRenderer::addLog("공격할 수단이 없다. 무가서를 읽어야 한다.");
		return false;
	}

	for (auto& e : skills)
	{
		skillChoice.push_back(std::to_string(++count) + "." + toString(e) + " / 기력 소모 : " + std::to_string(DataManager::getInstance().getSkillStamina(e)));
	}

	skillChoice.push_back("0. 취소");

	UIRenderer::printCombatScreen(m_monsters, m_player, skillChoice);

	//스킬 입력
	int skillInput = InputHandler::getInt(0, skills.size(), [&]() {UIRenderer::printCombatScreen(m_monsters, m_player, skillChoice); });

	if (skillInput == 0)
		return false;

	SkillType selected = skills[skillInput - 1];

	if (m_player.getStamina() < DataManager::getInstance().getSkillStamina(selected))
	{
		UIRenderer::addLog("기력이 부족하다.");
		return false;
	}

	//스킬 커맨드 실행
	auto skill = createSkillCommand(selected);

	int targetIndex = selectTarget(selected);

	skill->execute(m_player, m_monsters, targetIndex, [](LogLine log) {UIRenderer::addLog(log); });

	checkMonsters();

	return true;
}

bool CombatSystem::executeDefendCommand()
{
	DefendCommand().execute(m_player, m_monsters, 0, [](LogLine log) {UIRenderer::addLog(log); });
	return true;
}

bool CombatSystem::executeFleeCommand()
{
	FleeCommand fleecommand;
	fleecommand.execute(m_player, m_monsters, 0, [](LogLine log) {UIRenderer::addLog(log); });

	if (fleecommand.isFleeSuccess())
	{
		m_result = CombatResult::Fled;
		combatEnd();
	}

	return true;
}

bool CombatSystem::handleItemInCombat()
{
	auto& inven = m_player.getInven();

	if (inven.empty())
	{
		UIRenderer::addLog("소지품이 없다.");
		return false;
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
	itemChoices.push_back("0. 취소");

	UIRenderer::printInvenScreen(itemList, m_player, itemChoices);

	int input = InputHandler::getInt(0, count, [&]() {UIRenderer::printInvenScreen(itemList, m_player, itemChoices); });

	if (input == 0)
	{
		return false;
	}

	std::string selectedId = itemList[input - 1].first;
	m_player.useItem(selectedId);

	std::vector<LogSegment>log;
	log.push_back(LogSegment("[" + DataManager::getInstance().getItemName(selectedId) + "]", Color::CYAN));
	log.push_back(LogSegment(" 을/를 사용했다.", Color::WHITE));
	UIRenderer::addLog(log);

	return true;
}

int CombatSystem::selectTarget(SkillType selected)
{
	if (selected == SkillType::Neoul || selected == SkillType::Gumni)
		return 0;
	if (m_monsters.size() == 1)
		return 0;
	printTargetChoice();
	return InputHandler::getInt(1, m_monsters.size(), [&]() {printTargetChoice(); }) - 1;
}

void CombatSystem::checkMonsters()
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

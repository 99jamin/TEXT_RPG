#pragma once
#include <vector>
#include "CombatResult.h"
#include "SkillType.h"

class Player;
class Monster;

class CombatSystem
{

public:

	CombatSystem(Player& player, std::vector<Monster*>monsters);
	
	CombatResult combatStart();

private:

	Player& m_player;
	std::vector<Monster*> m_monsters;
	bool m_isRunning = true;

	CombatResult m_result = CombatResult::Victory;

	static constexpr int POISON_DAMAGE = 5;

	void playerTurn();

	void monsterTurn(Monster& monster);

	void combatEnd();

	void printTargetChoice();

	bool checkPlayerStatus();

	bool executeSkillCommand();
	
	bool executeDefendCommand();

	bool executeFleeCommand();

	bool handleItemInCombat();

	int selectTarget(SkillType selected);

	void checkMonsters();
};

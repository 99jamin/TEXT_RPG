#pragma once
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include "GameState.h"
#include "../combat/CombatResult.h"

class Monster;
class CombatSystem;
class GameManager;

class CombatState : public GameState
{
public:

	CombatState(int monsterCount, std::string monsterId, std::function<void(CombatResult)> onResult);

	~CombatState();

	void enter(GameManager& manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

	void pause(GameManager& manager) override {}

	void resume(GameManager& manager) override {}

private:
	std::function<void(CombatResult)> m_onResult;
	std::vector<std::unique_ptr<Monster>> m_monsters;
	std::unique_ptr<CombatSystem> m_combatSystem;
};


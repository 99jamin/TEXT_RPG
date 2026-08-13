#include "CombatState.h"
#include "../combat/CombatResult.h"
#include "GameManager.h"
#include "../entity/Monster.h"
#include "../combat/CombatSystem.h"
#include "../data/DataManager.h"
#include "../combat/MonsterFactory.h"
#include "../sound/SoundManager.h"

CombatState::CombatState(int monsterCount, std::string monsterId, std::function<void(CombatResult)> onResult)
	: m_onResult(onResult)
{
	MonsterData data = DataManager::getInstance().getMonsterData(monsterId);
	
	for (int i = 0; i < monsterCount; i++)
	{
		m_monsters.push_back(MonsterFactory::create(data));
	}
}

CombatState::~CombatState() = default;

void CombatState::enter(GameManager& manager)
{

	std::vector<Monster*> rawPtrs;
	for (auto& m : m_monsters)
		rawPtrs.push_back(m.get());
	m_combatSystem = std::make_unique<CombatSystem>(manager.getPlayer(), rawPtrs);

	if (m_monsters[0]->isLastBoss())
		SoundManager::play("bgm/lastboss.mp3");
	else if (m_monsters[0]->isBoss())
		SoundManager::play("bgm/boss.mp3");
	else
		SoundManager::play("bgm/combat.mp3");

}

void CombatState::update(GameManager& manager)
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

void CombatState::exit(GameManager& manager)
{
	SoundManager::stop();
}



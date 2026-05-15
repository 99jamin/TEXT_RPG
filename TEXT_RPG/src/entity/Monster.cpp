#include "Monster.h"

 Monster::Monster(const MonsterData& data)
	:Entity(data.name, data.hp, data.attack, data.defense), m_effect(data.effect), m_dropItemId(data.dropItemId), m_attackLog(data.attackLog),m_art(data.art),m_art2(data.art2), m_phaseTwoLog(data.phaseTwoLog)
{

}

void Monster::printStatus() const
{

}

void Monster::dead()
{
	Entity::setCurHp(0);
}

const std::string& Monster::getAttackLog() const
{
	return m_attackLog;
}

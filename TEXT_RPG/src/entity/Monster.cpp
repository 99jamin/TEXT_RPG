#include "Monster.h"

 Monster::Monster(const MonsterData& data)
	:Entity(data.name, data.hp, data.attack, data.defense), m_effect(data.effect), m_dropItemId(data.dropItemId), m_attackLog(data.attackLog),m_art(data.art),m_art2(data.art2), m_phaseTwoLog(data.phaseTwoLog)
{

}

 const std::string& Monster::getPhaseTwoLog() const
 {
	 return m_phaseTwoLog;
 }

const std::string& Monster::getAttackLog() const
{
	return m_attackLog;
}

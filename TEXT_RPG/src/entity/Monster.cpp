#include "Monster.h"

 Monster::Monster(const std::string& name, int maxHp, int atk, int def, MonsterEffect effect)
	:Entity(name, maxHp, atk, def), m_effect(effect)
{

}

void Monster::printStatus() const
{

}

void Monster::dead()
{

}

#include "Monster.h"

 Monster::Monster(const MonsterData& data)
	:Entity(data.name, data.hp, data.attack, data.defense), m_effect(data.effect), m_dropItemId(data.dropItemId), m_description(data.description)
{

}

void Monster::printStatus() const
{

}

void Monster::dead()
{
	if (m_dropItemId.has_value()) {

	}
}

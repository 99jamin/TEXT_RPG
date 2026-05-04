#include "Entity.h"
#include "../ui/UIRenderer.h"

Entity::Entity(const std::string& name, int maxHp, int atk, int def)
	:m_name(name), m_maxHp(maxHp), m_atk(atk), m_def(def)
{
	m_curHp = m_maxHp;
}

void Entity::takeDamage(int damage)
{

	if (isAlive())
	{
		int actualDamage = std::max(0, damage - m_def);
		m_curHp -= actualDamage;
		m_curHp = std::max(0, m_curHp);
		UIRenderer::addLog(m_name + " 은 " + std::to_string(actualDamage)+" 의 피해를 입었다.");
	}

	if (!isAlive())
		dead();
}

void Entity::recoverHp(int amount)
{
	m_curHp += amount;
	m_curHp = std::min(m_maxHp, m_curHp);
}

bool Entity::isAlive() const
{
	return (m_curHp > 0);
}

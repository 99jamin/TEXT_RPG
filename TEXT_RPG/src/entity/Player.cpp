#include "Player.h"
#include "Item.h"
#include "../data/DataManager.h"
#include <vector>
#include <algorithm>

Player::Player(const std::string& name, int maxHp, int atk, int def, int maxStamina)
	:Entity(name, maxHp, atk, def), m_maxStamina(maxStamina), m_stamina(maxStamina)
{

}

void Player::init()
{
	Entity::setAtk(15);
	Entity::setDef(0);
	Entity::setCurHp(Entity::getMaxHp());
	m_maxStamina = 5;
	m_stamina = 1;
	m_skills = {};
	m_inven = {};
	m_isConcentrating = false;
	m_wasHitWhileConcentrating = false;
	m_isDefending = false;
	m_isPoison = false;
}

int Player::takeDamage(int damage)
{
	if (m_isConcentrating)
		hitWhileConcentrating();

	if (m_isDefending)
	{
		damage /= 2;
		endDefend();
	}

	return Entity::takeDamage(damage);
}

void Player::printStatus() const
{
	
}

void Player::dead()
{

}

void Player::learnSkill(SkillType skill)
{
	if (!hasSkill(skill))
		m_skills.push_back(skill);

}

bool Player::hasSkill(SkillType skill) const
{
	return (std::find(m_skills.begin(), m_skills.end(), skill) != m_skills.end());
}

void Player::consumeStamina(int amount)
{
	m_stamina -= amount;
	m_stamina = std::max(0, m_stamina);
}

void Player::recoverStamina(int amount)
{
	m_stamina += amount;
	m_stamina = std::min(m_maxStamina, m_stamina);
}


//Save
void Player::loadFromSave(int curHp, int stamina, bool poisoned, std::map<std::string, int> inventory, std::vector<SkillType> skills)
{
	Entity::setCurHp(curHp);
	m_stamina = stamina;
	m_isPoison = poisoned;
	m_inven = inventory;
	m_skills = skills;
}

void Player::startConcentrate()
{
	m_isConcentrating = true;
}

void Player::hitWhileConcentrating()
{
	m_wasHitWhileConcentrating = true;
}

bool Player::isConcentrating() const
{
	return m_isConcentrating;
}

bool Player::wasHitWhileConcentrating() const
{
	return m_wasHitWhileConcentrating;
}

void Player::endConcentrate()
{
	m_isConcentrating = false;
	m_wasHitWhileConcentrating = false;
}

void Player::applyPoison() { m_isPoison = true; }

void Player::curePoison() { m_isPoison = false; }

bool Player::isPoisoned() const { return m_isPoison; }

void Player::drainStamina(int amount)
{
	m_stamina -= amount;
	m_stamina = std::max(0, m_stamina);
}

//inven
void Player::addItem(const std::string& id, int count)
{
	m_inven[id] += count;
}

void Player::removeItem(const std::string& id)
{
	if (m_inven[id] <= 0)
		return;

	m_inven[id]--;

	if (m_inven[id] == 0)
		m_inven.erase(id);
}

bool Player::hasItem(const std::string& id) const
{
	auto it = m_inven.find(id);
	return (it != m_inven.end() && it->second > 0);
}

void Player::useItem(const std::string& id)
{
	if (!hasItem(id)) return;
	ItemData data = DataManager::getInstance().getItemData(id);
	Item item(data);
	item.useItem(*this);
	removeItem(id);
		
}

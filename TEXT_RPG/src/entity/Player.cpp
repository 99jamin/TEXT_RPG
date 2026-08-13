#include "Player.h"
#include "Item.h"
#include "../data/DataManager.h"
#include <vector>
#include <algorithm>

Player::Player()
	:Entity(initialName, initialHp, initialAtk, initialDef), m_maxStamina(initialStamina), m_stamina(1), m_fleshCount(initialfleshCount)
{

}

void Player::init()
{
	Entity::setAtk(initialAtk);
	Entity::setDef(initialDef);
	Entity::setCurHp(Entity::getMaxHp());
	m_maxStamina = initialStamina;
	m_stamina = 1;
	m_fleshCount = initialfleshCount;
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

int Player::takeFixedDamage(int amount)
{
	return Entity::takeFixedDamage(amount);
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

void Player::evolution(int atkAmount, int defAmount)
{
	Entity::setAtk(Entity::getAtk() + atkAmount);
	Entity::setDef(Entity::getDef() + defAmount);
}


//Save
void Player::loadFromSave(int curHp, int atk, int def, int stamina, int fleshCount, bool poisoned, std::map<std::string, int> inventory, std::vector<SkillType> skills)
{
	Entity::setCurHp(curHp);
	Entity::setAtk(atk);
	Entity::setDef(def);
	m_stamina = stamina;
	m_isPoison = poisoned;
	m_inven = inventory;
	m_skills = skills;
	m_fleshCount = fleshCount;
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

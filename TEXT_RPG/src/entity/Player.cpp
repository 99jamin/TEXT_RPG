#include "Player.h"
#include <vector>
#include <algorithm>

Player::Player(const std::string& name, int maxHp, int atk, int def, int maxStamina)
	:Entity(name, maxHp, atk, def), m_maxStamina(maxStamina), m_stamina(maxStamina)
{

}

void Player::takeDamage(int damage)
{
	if (m_isChargingGumni)
		setHitWhileCharging();

	if (m_isDefending)
		damage /= 2;  

	Entity::takeDamage(damage);
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

void Player::startGumniCharge()
{
	m_isChargingGumni = true;
}

void Player::setHitWhileCharging()
{
	m_wasHitWhileCharging = true;
}

bool Player::isChargingGumni() const
{
	return m_isChargingGumni;
}

bool Player::wasHitWhileCharging() const
{
	return m_wasHitWhileCharging;
}

void Player::releaseGumni()
{
	m_isChargingGumni = false;
	m_wasHitWhileCharging = false;
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
void Player::addItem(const std::string& id)
{
	m_inven[id]++;
}

void Player::removeItem(const std::string& id)
{
	if (m_inven[id] <= 0)
		return;

	m_inven[id]--;
}

bool Player::hasItem(const std::string& id) const
{
	auto it = m_inven.find(id);
	return (it != m_inven.end() && it->second > 0);
}

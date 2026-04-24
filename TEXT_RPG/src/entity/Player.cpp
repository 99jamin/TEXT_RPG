#include "Player.h"

Player::Player(const std::string& name, int maxHp, int atk, int def, int maxStamina)
	:Entity(name, maxHp, atk, def), m_maxStamina(maxStamina), m_stamina(maxStamina)
{

}

void Player::printStatus() const
{

}

void Player::dead()
{
	//게임 오버 연출
	//타이틀 화면으로 전환
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

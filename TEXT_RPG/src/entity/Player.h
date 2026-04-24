#pragma once
#include <vector>
#include <algorithm>
#include "Entity.h"
#include "../combat/SkillType.h"

class Player : public Entity
{

public:

	Player(const std::string& name, int maxHp, int atk, int def, int maxStamina);

	void printStatus() const override;

	void dead() override;

	void learnSkill(SkillType skill);

	bool hasSkill(SkillType skill) const;

	void consumeStamina(int amount);

	void recoverStamina(int amount);

	
	const std::vector<SkillType>& getSkills() const { return m_skills; }
	int getStamina() const { return m_stamina; }
	int getMaxStamina() const { return m_maxStamina; }

private:

	std::vector<SkillType> m_skills;
	//std::vector<Item> m_inven;
	int m_stamina;
	int m_maxStamina;
};

#pragma once
#include "Entity.h"
#include "../combat/SkillType.h"
#include <vector>
#include <map>

class Player : public Entity
{

public:

	Player(const std::string& name, int maxHp, int atk, int def, int maxStamina);

	void takeDamage(int damage);

	void printStatus() const override;

	void dead() override;

	void learnSkill(SkillType skill);

	bool hasSkill(SkillType skill) const;

	void consumeStamina(int amount);

	void recoverStamina(int amount);

	//getter
	const std::vector<SkillType>& getSkills() const { return m_skills; }
	int getStamina() const { return m_stamina; }
	int getMaxStamina() const { return m_maxStamina; }

	//Save
	void loadFromSave(int curHp, int stamina, bool poisoned, std::map<std::string, int> inventory, std::vector<SkillType> skills);

	//GumniCommand Flag
	void startGumniCharge();
	void setHitWhileCharging();
	bool isChargingGumni() const;
	bool wasHitWhileCharging() const;
	void releaseGumni();

	//Defecd Flag
	void startDefend() { m_isDefending = true; }
	void endDefend() { m_isDefending = false; }
	bool isDefending() const { return m_isDefending; }

	//Debuff Flag
	void applyPoison();
	void curePoison();
	bool isPoisoned() const;
	void drainStamina(int amount);

	//inven
	void addItem(const std::string& id, int count);
	void removeItem(const std::string& id);
	bool hasItem(const std::string& id) const;
	const std::map<std::string, int > getInven() const
	{
		return m_inven;
	}
	void useItem(const std::string& id);


private:

	std::vector<SkillType> m_skills;
	std::map<std::string,int> m_inven;

	int m_stamina;
	int m_maxStamina;

	bool m_isChargingGumni = false;
	bool m_wasHitWhileCharging = false;

	bool m_isDefending = false;

	bool m_isPoison = false;



};
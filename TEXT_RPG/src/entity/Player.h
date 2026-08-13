#pragma once
#include "Entity.h"
#include "../combat/SkillType.h"
#include <vector>
#include <map>

class Player : public Entity
{

public:

	Player();

	void init();

	int takeDamage(int damage);

	int takeFixedDamage(int amount) override;

	void learnSkill(SkillType skill);

	bool hasSkill(SkillType skill) const;

	void consumeStamina(int amount);

	void recoverStamina(int amount);

	void evolution(int atkAmount, int defAmount);

	void addFleshCount() { ++m_fleshCount; }

	//getter
	const std::vector<SkillType>& getSkills() const { return m_skills; }
	int getStamina() const { return m_stamina; }
	int getMaxStamina() const { return m_maxStamina; }
	const int getFleshCount() const { return m_fleshCount; }

	//Save
	void loadFromSave(int curHp, int atk, int def, int stamina, int fleshCount, bool poisoned, std::map<std::string, int> inventory, std::vector<SkillType> skills);

	//Concentrating Flag
	void startConcentrate();
	void hitWhileConcentrating();
	bool isConcentrating() const;
	bool wasHitWhileConcentrating() const;
	void endConcentrate();

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
	const std::map<std::string, int >& getInven() const
	{
		return m_inven;
	}
	void useItem(const std::string& id);


private:

	std::vector<SkillType> m_skills;
	std::map<std::string,int> m_inven;

	int m_stamina;
	int m_maxStamina;

	int m_fleshCount;

	bool m_isConcentrating = false;
	bool m_wasHitWhileConcentrating = false;

	bool m_isDefending = false;

	bool m_isPoison = false;

	//초기값
	static constexpr int initialHp = 100;
	static constexpr int initialAtk = 15;
	static constexpr int initialDef = 0;
	static constexpr int initialStamina = 5;
	static constexpr int initialfleshCount = 0;
	static inline const std::string initialName = "무명";
};
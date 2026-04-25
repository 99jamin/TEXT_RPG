#pragma once
#include "Monster.h"

class Boss : public Monster
{

public:

	Boss(const std::string& name, int maxHp, int atk, int def, MonsterEffect effect);

	void takeDamage(int damage) override;

	bool isPhaseTwo() const;

	virtual void onPhaseTwo() = 0;

private:

	bool m_isPhaseTwo = false;
	static constexpr float PHASE_TWO_THRESHOLD = 0.5f;

	void checkPhaseTransition();

};
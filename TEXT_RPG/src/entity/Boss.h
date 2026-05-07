#pragma once
#include "Monster.h"

class Boss : public Monster
{

public:
	
	using Monster::Monster;

	int takeDamage(int damage) override;

	bool isPhaseTwo() const;

	virtual void onPhaseTwo() = 0;

	bool isBoss() const override { return true; };

private:

	bool m_isPhaseTwo = false;
	static constexpr float PHASE_TWO_THRESHOLD = 0.5f;

	void checkPhaseTransition();

};
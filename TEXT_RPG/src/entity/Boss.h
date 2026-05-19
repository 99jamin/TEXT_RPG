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

	bool isLastBoss() const override { return false; }

	bool consumePhaseTwoTrigger() override;

private:

	bool m_isPhaseTwo = false;
	bool m_phaseTwoJustTriggered = false;

	static constexpr float PHASE_TWO_THRESHOLD = 0.5f;

	void checkPhaseTransition();


};
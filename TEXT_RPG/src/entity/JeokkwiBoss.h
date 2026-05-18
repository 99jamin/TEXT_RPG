#pragma once
#include "Boss.h"

class JeokkwiBoss : public Boss
{
public:

	using Boss::Boss;

	void onPhaseTwo() override
	{
		m_art = m_art2;
		setDef(PHASE_TWO_DEF);
		setCurHp(PHASE_TWO_HP);
	}

	bool isLastBoss() const override { return true; }

private:

	static constexpr int PHASE_TWO_HP = 1;
	static constexpr int PHASE_TWO_DEF = 99999;
};

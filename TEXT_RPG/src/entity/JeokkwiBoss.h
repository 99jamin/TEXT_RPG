#pragma once
#include "Boss.h"

class JeokkwiBoss : public Boss
{
public:

	using Boss::Boss;

	void onPhaseTwo() override
	{
		setDef(PHASE_TWO_DEF);
		setCurHp(PHASE_TWO_HP);
	}

private:

	static constexpr int PHASE_TWO_HP = 1;
	static constexpr int PHASE_TWO_DEF = 99999;
};

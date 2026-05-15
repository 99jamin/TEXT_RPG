#pragma once
#include "Boss.h"

class JeokgapsinBoss : public Boss
{
public:

	using Boss::Boss;

	void onPhaseTwo() override
	{
		m_art = m_art2;
		setAtk(getAtk() * PHASE_TWO_STAT_RATIO);
		setDef(getDef() * PHASE_TWO_STAT_RATIO);
		setCurHp(getMaxHp());
	}

private:

	static constexpr float PHASE_TWO_STAT_RATIO = 1.2f;
};

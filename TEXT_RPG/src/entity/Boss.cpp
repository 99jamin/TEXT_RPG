#include "Boss.h"


void Boss::takeDamage(int damage)
{
	Monster::takeDamage(damage);
	checkPhaseTransition();
}

void Boss::checkPhaseTransition()
{
	if (isPhaseTwo())
		return;

	float hpRatio = float(getCurHp()) / float(getMaxHp());

	if (hpRatio < PHASE_TWO_THRESHOLD)
	{
		m_isPhaseTwo = true;
		onPhaseTwo();
	}
		
}

bool Boss::isPhaseTwo() const
{
	return m_isPhaseTwo;
}

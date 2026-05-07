#include "Boss.h"


int Boss::takeDamage(int damage)
{
	int actualDamage = Monster::takeDamage(damage);
	checkPhaseTransition();

	return actualDamage;
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

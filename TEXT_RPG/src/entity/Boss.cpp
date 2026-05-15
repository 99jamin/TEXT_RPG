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
		m_phaseTwoJustTriggered = true;
		m_isPhaseTwo = true;
		onPhaseTwo();
	}
}

bool Boss::consumePhaseTwoTrigger()
{
	if (m_phaseTwoJustTriggered)
	{
		m_phaseTwoJustTriggered = false;
		return true;
	}

	return false;
}

bool Boss::isPhaseTwo() const
{
	return m_isPhaseTwo;
}

const std::string& Boss::getPhaseTwoLog() const
{
	return m_phaseTwoLog;
}

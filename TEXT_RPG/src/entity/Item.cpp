#include "Item.h"
#include "Player.h"

Item::Item(const ItemData& data)
	:m_id(data.id), m_name(data.name), m_description(data.description), m_effect(data.effect), m_value(data.value), m_skillId(data.skillId),m_useLog(data.useLog)
{
	
}

void Item::useItem(Player& player)
{
	switch (m_effect)
	{
	case ItemEffect::None:
	{
		break;
	}
	case ItemEffect::Evolution:
	{
		player.recoverHp(m_value);
		player.evolution(atkEvolutionAmount,defEvolutionAmount);
		break;
	}
	case ItemEffect::HpRestore:
	{
		player.recoverHp(m_value);
		break;
	}
	case ItemEffect::HpRestoreFull:
	{
		player.recoverHp(player.getMaxHp());
		break;
	}
	case ItemEffect::CurePoison:
	{
		player.curePoison();
		break;
	}
	case ItemEffect::StaminaRestore:
	{
		player.recoverStamina(m_value);
		break;
	}
	case ItemEffect::SkillLearn:
	{
		player.learnSkill(m_skillId);
		break;
	}

	}

}

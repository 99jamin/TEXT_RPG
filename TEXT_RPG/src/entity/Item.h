#pragma once
#include <string>
#include "../data/DataTypes.h"
#include "../combat/SkillType.h"
#include "ItemEffect.h"

class Player;

class Item
{
	
public:

	Item(const ItemData& data);

	void useItem(Player& player);

	const std::string& getId() const { return m_id; }
	const std::string& getName() const { return m_name; }
	const std::string& getDescription() const { return m_description; }

private:

	std::string m_id;
	std::string m_name;
	std::string m_description;
	std::string m_useLog;
	ItemEffect m_effect;
	int m_value;
	SkillType m_skillId;

	static constexpr int atkEvolutionAmount = 3;
	static constexpr int defEvolutionAmount = 1;
};
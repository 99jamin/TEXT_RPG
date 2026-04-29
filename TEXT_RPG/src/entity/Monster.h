#pragma once
#include "Entity.h"
#include "../combat/MonsterEffect.h"
#include "../data/DataTypes.h"
#include <optional>

class Monster : public Entity
{

public:
	Monster(const MonsterData& data);


	void printStatus() const override;

	void dead() override;

	MonsterEffect getEffect() const { return m_effect; }


protected:

	MonsterEffect m_effect;
	std::optional<std::string> m_dropItemId;
	std::string m_description;

};
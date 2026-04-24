#pragma once
#include "Entity.h"
#include "../combat/MonsterEffect.h"
//#include <optional>

class Monster : public Entity
{

public:
	Monster(const std::string& name, int maxHp, int atk, int def, MonsterEffect effect);


	void printStatus() const override;

	void dead() override;

	MonsterEffect getEffect() const { return m_effect; }


private:

	MonsterEffect m_effect;
	//std::optional<Item> m_dropItem;

};
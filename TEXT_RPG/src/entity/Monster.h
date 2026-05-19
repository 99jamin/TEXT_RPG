#pragma once
#include "Entity.h"
#include "../combat/MonsterEffect.h"
#include "../data/DataTypes.h"
#include <optional>

class Monster : public Entity
{

public:
	Monster(const MonsterData& data);

	MonsterEffect getEffect() const { return m_effect; }

	const std::string& getAttackLog() const;

	const std::vector<std::string>& getArt() const {return m_art; }
	
	virtual bool isBoss() const { return false; }

	virtual bool isLastBoss() const { return false; }

	virtual bool consumePhaseTwoTrigger() { return false; }

	const std::string& getPhaseTwoLog() const;

protected:

	MonsterEffect m_effect;
	std::optional<std::string> m_dropItemId;
	std::string m_attackLog;
	std::vector<std::string> m_art;
	std::string m_phaseTwoLog;
	std::vector<std::string> m_art2;

};
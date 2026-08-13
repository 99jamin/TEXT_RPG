#pragma once
#include <memory>
#include "../entity/Monster.h"
#include "../data/DataManager.h"
#include "../data/DataTypes.h"
#include "../entity/JeokgapsinBoss.h"
#include "../entity/JeokkwiBoss.h"

class MonsterFactory
{

public:

	static std::unique_ptr<Monster> create(const MonsterData& data)
	{
		if (data.id == "jeokgapsin")
		{
			return std::make_unique<JeokgapsinBoss>(data);
		}
		else if (data.id == "jeokkwi")
		{
			return std::make_unique<JeokkwiBoss>(data);
		}
		else
		{
			return std::make_unique<Monster>(data);
		}
	}

};
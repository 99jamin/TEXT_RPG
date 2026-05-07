#pragma once
#include "Command.h"
#include "../entity/Player.h"

class DefendCommand : public Command
{

public:

	int execute(Entity& user, Entity& target) override
	{
		Player* player = dynamic_cast<Player*>(&user);
		if (!player) return 0;

		player->startDefend();

		return 0;
	}


	std::string getDescription() const override
	{
		return "방어";
	}

};

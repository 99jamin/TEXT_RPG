#pragma once
#include "Command.h"
#include "../entity/Player.h"

class DefendCommand : public Command
{

public:

	void execute(Entity& user, Entity& target) override
	{
		Player* player = dynamic_cast<Player*>(&user);
		if (!player) return;

		player->startDefend();
	}


	std::string getDescription() const override
	{
		return "방어";
	}

};

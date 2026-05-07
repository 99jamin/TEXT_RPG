#pragma once
#include <string>
class Entity;

class Command
{
public:

	virtual int execute(Entity& user, Entity& target) = 0;
	virtual std::string getDescription() const = 0;
	virtual int getStaminaCost() const { return 0; }

};
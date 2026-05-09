#pragma once
#include <string>
#include <vector>
#include <functional>
#include "../ui/LogLine.h"

class Entity;

class Command
{
public:

	virtual void execute(Entity& user, std::vector<Entity*>& targets, int targetIndex, std::function<void(LogLine)> logCallback = nullptr) = 0;

protected:

	LogLine m_log;
};
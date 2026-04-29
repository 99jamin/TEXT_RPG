#include "src/core/GameManager.h"
#include "src/core/TitleState.h"
#include "src/data/DataManager.h"
#include <Windows.h>
#include <iostream>


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	DataManager::getInstance().loadAll();

	MonsterData data = DataManager::getInstance().getMonsterData("plague_fisherman");
	std::cout << data.name << std::endl;
	std::cout << data.description << std::endl;
	std::cout << data.hp << std::endl;

	GameManager manager;

	manager.pushState(std::make_unique<TitleState>());

	manager.run();

	return 0;
}
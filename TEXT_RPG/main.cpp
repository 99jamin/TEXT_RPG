#include "src/core/GameManager.h"
#include "src/core/TitleState.h"
#include "src/data/DataManager.h"
#include "src/ui/UIRenderer.h"
#include <Windows.h>
#include <iostream>


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	system("mode con cols=140 lines=50");

	DataManager::getInstance().loadAll();

	////몬스터 데이터 테스트
	//MonsterData data = DataManager::getInstance().getMonsterData("plague_fisherman");
	//std::cout << data.name << std::endl;
	//std::cout << data.description << std::endl;
	//std::cout << data.hp << std::endl;

	////맵 데이터 테스트
	//MapData data2 = DataManager::getInstance().getMapData("village");
	//std::cout << data2.name << std::endl;
	//std::cout << data2.rooms.size() << std::endl;

	////맵 출력 테스트
	//Map map(data2);

	GameManager manager;

	manager.pushState(std::make_unique<TitleState>());

	manager.run();

	return 0;
}
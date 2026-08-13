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
	system("mode con cols=140 lines=41");

	GameManager manager;

	manager.pushState(std::make_unique<TitleState>());

	manager.run();

	return 0;
}
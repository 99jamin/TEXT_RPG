#include <iostream>
#include "TitleState.h"
#include "GameManager.h"
#include "ExploreState.h"

void TitleState::enter(GameManager& manager)
{

}

void TitleState::update(GameManager& manager)
{

	UIRenderer::printTitleScreen();

	int input;
	std::cin >> input;

	if (input == 1)
		manager.pushState(std::make_unique<ExploreState>("village"));
	
	if (input == 2)
	{
		if (!SaveManager::getInstance().hasSave())
		{
			UIRenderer::printTitleScreen("이전 기록이 없습니다.");
			return;
		}
			
		SaveManager::getInstance().loadData();

		auto& pd = SaveManager::getInstance().getPlayerData();
		manager.getPlayer().loadFromSave(pd.hp, pd.stamina, pd.poisoned, pd.inventory, pd.skills);
		manager.pushState(std::make_unique<ExploreState>(SaveManager::getInstance().getMapId(), true));
	}

	if (input == 3)
		manager.quit();
}

void TitleState::exit(GameManager& manager)
{

}

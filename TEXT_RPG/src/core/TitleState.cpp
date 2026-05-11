#include <iostream>
#include "TitleState.h"
#include "GameManager.h"
#include "ExploreState.h"
#include "PrologueState.h"
#include "../save/SaveManager.h"
#include "../ui/UIRenderer.h"
#include "../input/InputHandler.h"

void TitleState::enter(GameManager& manager)
{

}

void TitleState::update(GameManager& manager)
{

	UIRenderer::printTitleScreen();

	int input = InputHandler::getInt(1, 3,[&](){UIRenderer::printTitleScreen(); });

	if (input == 1)
	{
		m_startNewGame = true;
		manager.getPlayer().init();
		manager.pushState(std::make_unique<PrologueState>());
	}
	
	if (input == 2)
	{
		if (!SaveManager::getInstance().hasSave())
		{
			//UIRenderer::printTitleScreen("이전 기록이 없습니다.");
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

void TitleState::pause(GameManager& manager) {}

void TitleState::resume(GameManager& manager)
{
	if (m_startNewGame)
	{
		m_startNewGame = false;
		manager.pushState(std::make_unique<ExploreState>("village"));
	}
}

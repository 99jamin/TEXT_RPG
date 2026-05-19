#include <iostream>
#include "TitleState.h"
#include "GameManager.h"
#include "ExploreState.h"
#include "PageState.h"
#include "../data/DataManager.h"
#include "../save/SaveManager.h"
#include "../ui/UIRenderer.h"
#include "../input/InputHandler.h"
#include "../sound/SoundManager.h"

void TitleState::enter(GameManager& manager)
{
	SoundManager::play("bgm/title.mp3");
}

void TitleState::update(GameManager& manager)
{

	UIRenderer::printTitleScreen();

	int input = InputHandler::getInt(1, 3,[&](){UIRenderer::printTitleScreen(); });

	if (input == 1)
	{
		m_startNewGame = true;
		manager.getPlayer().init();
		manager.pushState(std::make_unique<PageState>(DataManager::getInstance().getPrologueData(), "bgm/prologue.mp3",
			[](GameManager& m) {m.popState(); }));
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
		manager.getPlayer().loadFromSave(pd.hp, pd.atk, pd.def, pd.stamina, pd.fleshCount, pd.poisoned, pd.inventory, pd.skills);
		manager.pushState(std::make_unique<ExploreState>(SaveManager::getInstance().getMapId(), true));
	}

	if (input == 3)
		manager.quit();
}

void TitleState::exit(GameManager& manager)
{
	SoundManager::stop();
}

void TitleState::pause(GameManager& manager) 
{
	SoundManager::stop();
}

void TitleState::resume(GameManager& manager)
{
	SoundManager::play("bgm/title.mp3");

	if (m_startNewGame)
	{
		m_startNewGame = false;
		manager.pushState(std::make_unique<ExploreState>("village"));
	}
}

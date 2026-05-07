#include "GameManager.h"
#include "TitleState.h"

GameManager::GameManager()
	:running(true),
	m_player(std::make_unique<Player>("엄마",1000,15,0,5))
{

}

GameManager::~GameManager()
{
	while (!stateStack.empty())
	{
		stateStack.top()->exit(*this);
		stateStack.pop();
	}
}

void GameManager::pushState(std::unique_ptr<GameState> state)
{
	if (!stateStack.empty())
	{
		stateStack.top()->exit(*this);
	}

	stateStack.push(std::move(state));
	stateStack.top()->enter(*this);

}

void GameManager::popState()
{
	if (!stateStack.empty())
	{
		stateStack.top()->exit(*this);
		stateStack.pop();
	}

	if (!stateStack.empty())
	{
		stateStack.top()->enter(*this);
	}
}

void GameManager::changeState(std::unique_ptr<GameState> state)
{
	if (!stateStack.empty())
	{
		stateStack.top()->exit(*this);
		stateStack.pop();
	}

	stateStack.push(std::move(state));
	stateStack.top()->enter(*this);
}

void GameManager::run()
{
	while (running && !stateStack.empty())
	{
		stateStack.top()->update(*this);
	}
}

void GameManager::quit()
{
	running = false;
}

void GameManager::gameover()
{
	while (!stateStack.empty())
	{
		stateStack.top()->exit(*this);
		stateStack.pop();
	}

	pushState(std::make_unique<TitleState>());
}

bool GameManager::isRunning() const
{
	return running;
}

Player& GameManager::getPlayer()
{
	return *m_player;
}

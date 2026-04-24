#include "GameManager.h"

GameManager::GameManager()
	:running(true) {}

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

bool GameManager::isRunning() const
{
	return running;
}

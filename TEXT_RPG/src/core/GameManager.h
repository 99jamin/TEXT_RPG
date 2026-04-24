#pragma once
#include <stack>
#include <memory>
#include "GameState.h"

class GameManager {

public:
	GameManager();

	~GameManager();

	void pushState(std::unique_ptr<GameState>state);

	void popState();

	void changeState(std::unique_ptr<GameState>state);

	void run();

	void quit();

	bool isRunning() const;


private:

	std::stack<std::unique_ptr<GameState>> stateStack;
	bool running;

};
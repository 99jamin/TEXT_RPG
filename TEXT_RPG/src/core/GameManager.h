#pragma once
#include <stack>
#include <memory>
#include "GameState.h"
#include "../entity/Player.h"

class GameManager {

public:
	GameManager();

	~GameManager();

	void pushState(std::unique_ptr<GameState>state);

	void popState();

	void changeState(std::unique_ptr<GameState>state);

	void run();

	void quit();

	void gameover();

	bool isRunning() const;

	Player& getPlayer();

	const Player& getPlayer() const;

private:

	std::stack<std::unique_ptr<GameState>> stateStack;
	std::unique_ptr<Player> m_player;
	bool running;

};
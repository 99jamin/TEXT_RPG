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

private:

	const std::string initialName = "무명";
	const int initialHp = 100;
	const int initialAtk = 10;
	const int initialDef = 10;
	const int initialStamina = 5;

	std::stack<std::unique_ptr<GameState>> stateStack;
	std::unique_ptr<Player> m_player;
	bool running;

};
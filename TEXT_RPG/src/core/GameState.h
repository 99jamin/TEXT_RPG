#pragma once

class GameManager;

class GameState {

public:

	virtual ~GameState() = default;
	virtual void enter(GameManager & manager) = 0;
	virtual void update(GameManager & manager) = 0;
	virtual void exit(GameManager & manager) = 0;

};
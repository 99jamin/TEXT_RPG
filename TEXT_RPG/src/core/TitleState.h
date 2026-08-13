#pragma once
#include "GameState.h"

class GameManager;

class TitleState : public GameState
{
public:
	void enter(GameManager& manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

	void pause(GameManager& manager) override;

	void resume(GameManager& manager)override;

private:
	bool m_startNewGame = false;
};


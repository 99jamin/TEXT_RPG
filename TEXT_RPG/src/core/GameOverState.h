#pragma once
#include "GameState.h"

class GameManager;

class GameOverState : public GameState
{

public:

	void enter(GameManager& manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

private:

};
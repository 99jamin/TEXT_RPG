#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include "../data/DataTypes.h"
class GameManager;

class HiddenEndingState : public GameState
{
public:

	HiddenEndingState();

	void enter(GameManager& manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

private:

	std::vector<PageData>m_pages;
	int m_currentPage = 0;

};
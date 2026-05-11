#pragma once
#include "GameState.h"
#include <vector>
#include <string>
class GameManager;

struct ProloguePage
{
	std::vector<std::string> art;
	std::vector<std::string> lines;
};

class PrologueState : public GameState
{
public:

	PrologueState();

	void enter(GameManager&manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

private:

	std::vector<ProloguePage>m_pages;
	int m_currentPage = 0;
	bool m_textDone = false;

};
#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include <functional>
#include "../data/DataTypes.h"

class GameManager;

class PageState : public GameState
{
public:

	PageState(const std::vector<PageData>& pages, const std::string& bgm, std::function<void(GameManager&)> onFinish);

	void enter(GameManager& manager) override;

	void update(GameManager& manager) override;

	void exit(GameManager& manager) override;

private:

	std::vector<PageData>m_pages;
	std::string m_bgm;
	std::function<void(GameManager&)> m_onFinish;
	int m_currentPage = 0;

};
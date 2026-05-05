#include "UIRenderer.h"
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "../data/DataManager.h"
std::vector<std::string> UIRenderer::s_logs;

 void UIRenderer::printExploreScreen(const Map& map, const Player& player, const std::vector<std::string>& choices)
{
	system("cls");

	printLayout(player, [&]() { printMiniMap(map); }, choices);
}

 void UIRenderer::printCombatScreen(const std::vector<Monster*>& monsters, const Player& player, const std::vector<std::string>& choices)
{
	system("cls");

	printLayout(player, [&]() { printEnemyInfo(monsters); }, choices);
}

 void UIRenderer::printInvenScreen(const std::vector<std::pair<std::string, int>>& itemList, const Player& player, const std::vector<std::string>& choices)
{
	system("cls");

	printLayout(player, [&]() { printItemInfo(itemList); }, choices);
}



 void UIRenderer::printTitleScreen()
{
	 //TODO: 타이틀 구현
}

 void UIRenderer::addLog(const std::string& log)
{
	s_logs.push_back(log);
	if (s_logs.size() > 20)
		s_logs.erase(s_logs.begin());
}

 void UIRenderer::clearLogs()
{
	s_logs.clear();
}

 void UIRenderer::printLayout(const Player& player, std::function<void()> rightPanelFn, const std::vector<std::string>& choices)
{
	// 상단 구분선 + 스탯바
	setCursor(0, 0);
	std::cout << std::string(TOTAL_WIDTH, '=');
	printStatBar(player);
	setCursor(0, 4);
	std::cout << std::string(TOTAL_WIDTH, '=');

	// 로그 영역 (왼쪽) + 세로 구분선
	for (int i = 0; i < 20; i++)
	{
		setCursor(0, LOG_START_ROW + i);
		std::cout << std::string(LEFT_WIDTH, ' ');  // 빈 줄로 영역 확보
		setCursor(LEFT_WIDTH, LOG_START_ROW + i);
		std::cout << "|";
	}

	// 로그 출력
	for (int i = 0; i < (int)s_logs.size(); i++)
	{
		setCursor(1, LOG_START_ROW + i);
		std::cout << s_logs[i];
	}

	// 오른쪽 패널
	rightPanelFn();

	// 하단 구분선 + 선택지
	setCursor(0, SEP_ROW);
	std::cout << std::string(TOTAL_WIDTH, '=');
	for (int i = 0; i < (int)choices.size(); i++)
	{
		setCursor(3, CHOICE_ROW + i * 2);
		std::cout << " " << choices[i];
	}
	setCursor(0, CHOICE_ROW + (int)choices.size() * 2 + 1);
	std::cout << std::string(TOTAL_WIDTH, '=');

	setCursor(0, CHOICE_ROW + (int)choices.size() * 2 + 2);
	std::cout << " > ";
}

 void UIRenderer::printStatBar(const Player& player)
{
	int hpBar = (player.getCurHp() * 20) / player.getMaxHp();
	std::string condition = player.isPoisoned() ? "역병" : "없음";

	setCursor(3, STAT_ROW);
	std::cout << "체력 : ";
	for (int i = 1; i <= 20; ++i)
	{
		if (i <= hpBar)
		{
			std::cout << "█";
		}
		else
		{
			std::cout << "░";
		}
	}

	setCursor(43, STAT_ROW);  // 기력 시작 x 고정
	std::cout << "기력 : ";
	for (int i = 1; i <= player.getMaxStamina(); ++i)
	{
		if (i <= player.getStamina())
		{
			std::cout << "◆";
		}
		else
		{
			std::cout << "◇";
		}
	}

	setCursor(73, STAT_ROW);  // 상태이상 시작 x 고정
	std::cout << "상태이상 : " << condition;
}

 void UIRenderer::printEnemyInfo(const std::vector<Monster*>& monsters)
{
	for (int i = 0; i < (int)monsters.size(); ++i)
	{
		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i));
		std::cout << i + 1 << ". " << monsters[i]->getName();

		int hpBar = (monsters[i]->getCurHp() * 10) / monsters[i]->getMaxHp();
		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i) + 1);
		for (int j = 1; j <= 10; ++j)
		{
			if (j <= hpBar)
			{
				std::cout << "█";
			}
			else
			{
				std::cout << "░";
			}
		}
	}
}

 void UIRenderer::printItemInfo(const std::vector<std::pair<std::string, int>>& itemList)
{
	for (int i = 0; i < (int)itemList.size(); ++i)
	{
		ItemData data = DataManager::getInstance().getItemData(itemList[i].first);

		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i));
		std::cout << i + 1 << ". " << data.name;
		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i) + 1);
		std::cout << data.description;
	}
}


 void UIRenderer::printMapInfo(const Map& map)
{
	setCursor(RIGHT_COL, LOG_START_ROW);
	std::cout << "위치 : " << map.getName();
	setCursor(RIGHT_COL, LOG_START_ROW + 1);
	std::cout << map.getDescription();
}

 void UIRenderer::printMiniMap(const Map& map)
{
	printMapInfo(map);

	int curX = map.getCurrentX();
	int curY = map.getCurrentY();
	auto& gird = map.getRoomGrid();

	for (int y = 0; y < 6; ++y)
	{
		setCursor(RIGHT_COL, LOG_START_ROW + 3 + y);
		for (int x = 0; x < 6; ++x)
		{
			if (!gird[y][x])
			{
				std::cout << "  ";
			}
			else if (x == curX && y == curY)
			{
				std::cout << "■";
			}
			else
			{
				std::cout << "□";
			}
		}
	}
}

 void UIRenderer::setCursor(int x, int y)
{
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

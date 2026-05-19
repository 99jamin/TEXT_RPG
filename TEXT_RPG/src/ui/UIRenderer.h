#pragma once
#define NOMINMAX
#include <functional>
#include <iostream>
#include <windows.h>
#include <vector>
#include "../map/Map.h"
#include "LogLine.h"

class Player;
class Monster;

class UIRenderer
{

public:

	static void printExploreScreen(const Map& map, const Player& player, const std::vector<std::string>& choices);

	static void printCombatScreen(const std::vector<Monster*>& monsters, const Player& player, const std::vector<std::string>& choices);

	static void printInvenScreen(const std::vector<std::pair<std::string, int>>& itemList, const Player& player, const std::vector<std::string>& choices);

	static void printTitleScreen(const std::string& message = "");

	static void printPageScreen(const std::vector<std::string>& art, const std::vector<std::string>& lines);

	static void printGameOverScreen();

	static void addLog(const std::string& log);

	static void addLog(const LogLine& line);

	static void clearLogs();

private:
	
	static void printLayout(const Player& player, std::function<void()> rightPanelFn, const std::vector<std::string>& choices);

	static void printStatBar(const Player& player);

	static void printEnemyInfo(const std::vector<Monster*>& monsters);

	static void printItemInfo(const std::vector<std::pair<std::string, int>>& itemList);

	static void printMapInfo(const Map& map);

	static void printMiniMap(const Map& map);

	static void setCursor(int x, int y);

	static void setColor(Color color);

	static void resetColor();

	static void clearConsole();

	static std::vector<LogLine> s_logs;

	static int s_newLogCount;

	// 레이아웃 행
	static const int STAT_ROW = 2;
	static const int LOG_START_ROW = 5;
	static const int LOG_END_ROW = 24;
	static const int SEP_ROW = 25;
	static const int CHOICE_ROW = 27;

	// 레이아웃 열
	static const int TOTAL_WIDTH = 140;
	static const int LEFT_WIDTH = 90;
	static const int RIGHT_COL = 96;

	// 스탯바 X좌표
	static const int STAMINA_X = 43;
	static const int STATUS_X = 73;

	// 로그
	static const int MAX_LOG_COUNT = 20;
	static const int LOG_TYPING_DELAY = 10;
	static const int PAGE_TYPING_DELAY = 20;

	// HP바
	static const int HP_BAR_LENGTH = 20;
	static const int ENEMY_HP_BAR_LENGTH = 30;
	static const float HP_DANGER_RATIO;

	// 적 정보
	static const int ENEMY_INFO_Y_OFFSET = 16;
	static const int ENEMY_INFO_SPACING = 4;

	// 선택지
	static const int CHOICES_PER_COLUMN = 5;

	// 타이틀/페이지 아트
	static const int TITLE_ART_WIDTH = 65;
	static const int PAGE_ART_WIDTH = 76;

	
};

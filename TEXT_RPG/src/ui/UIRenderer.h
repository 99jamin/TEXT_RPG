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

	static std::vector<LogLine> s_logs;

	static int s_newLogCount;

	static const int STAT_ROW = 2;   // 스탯바 행
	static const int LOG_START_ROW = 5;   // 로그 시작 행
	static const int LOG_END_ROW = 24;  // 로그 끝 행 (10줄)
	static const int SEP_ROW = 25;  // 구분선 행
	static const int CHOICE_ROW = 27;  // 선택지 시작 행

	static const int TOTAL_WIDTH = 140;	//총 너비
	static const int LEFT_WIDTH = 90;  // 왼쪽 패널 너비
	static const int RIGHT_COL = 96;  // 오른쪽 패널 시작 열

	
};

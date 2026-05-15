#include "UIRenderer.h"
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "../data/DataManager.h"
#include "../sound/SoundManager.h"
#include <conio.h>

std::vector<LogLine> UIRenderer::s_logs;
int UIRenderer::s_newLogCount = 0;

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



void UIRenderer::printTitleScreen(const std::string& message)
{
	 system("cls");

	 // 아스키 아트 (15줄, 가운데 상단)
	 std::vector<std::string> art = {
	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣶⣶⣦⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠘⣿⣷⣦⠀⠀⠀⠀⠈⣿⣿⡇⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣤⡀⠀⠀⠀⠀⠈⠙⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⢠⣿⣿⡟⠀⠀⠀⠀⣠⣿⣿⡇⠀⠀⠀⠀⠈⠛⠿⠿⠟⠛⠛⠛⠛⠛⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⣿⣿⣧⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⢠⣿⣿⣿⣧⠘⠻⣿⡿⢿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠙⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⢀⣴⣿⡟⠛⠛⣿⣿⣧⡀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⢠⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣴⣶⣶⣶⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⢀⣴⡿⠟⠁⠀⠀⠈⠻⢿⠇⠀⠀⢿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠙⠻⠿⠟⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠁⠀⠀⠀⣠⣤⣤⣄⣠⣤⣤⣤⣴⣾⣯⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡏⠀⠀⠀⠀⠀⠀⠐⢿⣿⣶⣶⠶⠿⠿⢿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠈⣿⣿⣿⠋⠉⠉⠉⠻⣿⣿⠁⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣴⣾⣿⣿⣶⣾⣶⣦⠀⠀⠀⢀⣠⣽⣿⣀⣀⣀⣀⣈⣿⣿⣗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⢠⣿⣿⠀⠀⠀⠈⠙⠻⠛⠛⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠈⢻⣿⣿⡟⠛⠛⠛⠛⠛⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣶⣶⣿⣿⡿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣷⣶⣶⣴⣶⣶⣾⣿⣶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⠀⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 };

	 int artStartX = (TOTAL_WIDTH - 65) / 2;
	 for (int i = 0; i < (int)art.size(); i++)
	 {
		 setCursor(artStartX, 3 + i);
		 std::cout << art[i];
	 }

	 // 선택지
	 int menuX = TOTAL_WIDTH / 2 - 8;
	 setCursor(menuX, 20);
	 std::cout << "1. 새로하기";
	 setCursor(menuX, 22);
	 std::cout << "2. 이어하기";
	 setCursor(menuX, 24);
	 std::cout << "3. 종료하기";

	 // 메시지
	 if (!message.empty())
	 {
		 setCursor(menuX, 27);
		 std::cout << message;
	 }

	 setCursor(menuX, 29);
	 std::cout << "> ";
}

 void UIRenderer::printPageScreen(const std::vector<std::string>& art, const std::vector<std::string>& lines)
 {
	 system("cls");

	 // 아트 출력 (중앙 정렬)
	 int artWidth = art.empty() ? 0 : 76;  // 아트 만들고 나서 조정
	 int artX = (TOTAL_WIDTH - artWidth) / 2;
	 for (int i = 0; i < (int)art.size(); i++)
	 {
		 setCursor(artX, 2 + i);
		 std::cout << art[i];
	 }

	 //텍스트 출력
	 bool skipped = false;
	 for (int i = 0; i < (int)lines.size(); i++)
	 {
		 setCursor(5, 25 + i*2);

		 if (skipped)
		 {
			 std::cout << lines[i];
			 continue;
		 }

		 int j = 0;
		 for (; j < (int)lines[i].size(); j++)
		 {
			 if (_kbhit()) { _getch(); skipped = true; break; }

			 if (j % 3 == 0)  // 2글자마다 한 번
				SoundManager::playSFX("sfx/typing1.wav");

			 std::cout << lines[i][j];
			 Sleep(20);
		 }

		 if (skipped)
			 std::cout << lines[i].substr(j);  // 끊긴 줄 나머지 즉시 출력
	 }

	 setCursor((TOTAL_WIDTH - 24) / 2, 35);
	 std::cout << "[ 아무 키나 누르면 계속... ]";
 }

 void UIRenderer::printGameOverScreen()
 {
	 system("cls");

	 // 아스키 아트 (15줄, 가운데 상단)
	 std::vector<std::string> art = {
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡀⠘⣿⡇⠀⣤⣤⣤⣤⢻⣿⠀⠀⠰⣤⣤⠘⣿⡆⠀⢀⣴⣦⣀⣹⣿⠀⠀⠀⢀⣿⣆⠀⠀⢀⣀⡀⠀⠈⢻⡇⠀⣀⣀⣀⣈⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡇⠀⣿⣇⣀⢻⣇⣸⣿⢸⣿⠶⠛⣿⣿⣟⠛⣿⣇⡀⢿⣇⣸⣿⣽⣿⠀⣰⣾⣛⣉⣙⣻⣇⡈⣿⡇⠀⠀⢸⡇⠀⣿⡏⠉⠁⣿⣇⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⢠⠿⠋⠻⡷⣿⡏⠉⠘⠋⣩⣿⣾⡏⠀⠐⣿⣤⣿⠇⣿⠉⠉⠀⠩⣿⡄⣾⡏⠀⠉⢿⣯⣉⣿⣯⠉⠁⢿⣷⡶⠶⢻⡇⠀⢿⣷⣶⠶⣿⡏⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠇⠀⠀⠀⢿⣧⣼⠟⠀⠀⠀⠉⠀⠀⣿⠀⠀⢠⡾⠛⣷⠟⢷⡆⠀⢸⣿⣭⣽⡿⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⢿⡇⠀⠺⠗⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	 };

	 int artStartX = (TOTAL_WIDTH - 65) / 2;
	 for (int i = 0; i < (int)art.size(); i++)
	 {
		 setCursor(artStartX, 3 + i);
		 std::cout << art[i];
	 }

	 // 선택지
	 int menuX = TOTAL_WIDTH / 2 - 8;
	 setCursor(menuX, 20);
	 std::cout << "1. 시작화면으로 돌아가기.";
	 setCursor(menuX, 22);
	 std::cout << "2. 종료하기.";
	 setCursor(menuX, 24);

	 setCursor(menuX, 29);
	 std::cout << "> ";
 }

void UIRenderer::addLog(const std::string& log)
{
	 LogLine line = { LogSegment(log, Color::WHITE) };

	s_logs.push_back(line);
	if (s_logs.size() > 20)
		s_logs.erase(s_logs.begin());

	s_newLogCount++;
}

void UIRenderer::addLog(const LogLine& line)
 {
	s_logs.push_back(line);
	if (s_logs.size() > 20)
		s_logs.erase(s_logs.begin());
	
	s_newLogCount++;
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

	// 로그 영역 (왼쪽)
	for (int i = 0; i < 20; i++)
	{
		setCursor(0, LOG_START_ROW + i);
		std::cout << std::string(LEFT_WIDTH, ' ');  // 빈 줄로 영역 확보
	}

	// 세로 구분선
	for (int i = 0; i <= CHOICE_ROW+4; ++i)
	{
		setCursor(LEFT_WIDTH, LOG_START_ROW + i);
		std::cout << "|";
	}

	// 오른쪽 패널
	rightPanelFn();

	// 하단 구분선 + 선택지
	setCursor(0, SEP_ROW);
	std::cout << std::string(LEFT_WIDTH, '=');
	setCursor(0, CHOICE_ROW + 10);
	std::cout << std::string(TOTAL_WIDTH, '=');

	// 로그 출력
	int logY = 0;
	int newStart = (int)s_logs.size() - s_newLogCount;

	bool skipped = false;

	for (int i = 0; i < (int)s_logs.size(); i++)
	{
		setCursor(1, LOG_START_ROW + logY++);
		bool isNew = (i >= newStart);

		for (auto& seg : s_logs[i])
		{
			setColor(seg.color);
			if (isNew && !skipped)
			{
				int j = 0;
				for (; j < (int)seg.text.size(); j++)
				{
					if (_kbhit()) { _getch(); skipped = true; break; }

					if (j % 5 == 0)  // 2글자마다 한 번
						SoundManager::playSFX("sfx/typing1.wav");

					std::cout << seg.text[j];
					Sleep(10);
				}
				if (skipped)
					std::cout << seg.text.substr(j);  // 끊긴 세그먼트 나머지 즉시 출력
			}
			else
			{
				std::cout << seg.text;
			}
		}
		resetColor();
	}

	s_newLogCount = 0;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));  // 버퍼 비우기


	for (int i = 0; i < (int)choices.size(); i++)
	{
		i < 5 ? setCursor(3, CHOICE_ROW + i * 2) : setCursor(30, CHOICE_ROW + (i-5) * 2);
		std::cout << " " << choices[i];
	}

	setCursor(0, CHOICE_ROW + 12);
	std::cout << " 선택 : ";
}

void UIRenderer::printStatBar(const Player& player)
{
	int hpBar = (player.getCurHp() * 20) / player.getMaxHp();
	std::string condition = player.isPoisoned() ? "역병" : "없음";

	setCursor(3, STAT_ROW);
	int threshold = player.getMaxHp() * 3 / 10;
	setColor(player.getCurHp() <= threshold ? Color::RED : Color::GREEN);
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
	setColor(Color::YELLOW);
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
	setColor(player.isPoisoned() ? Color::PURPLE : Color::WHITE);
	std::cout << "상태이상 : " << condition;
	resetColor();

}

 void UIRenderer::printEnemyInfo(const std::vector<Monster*>& monsters)
{
	 setColor(Color::RED);

	 if (monsters[0]->isBoss())
		 setColor(Color::BOSS); // 보스 색상

	 std::vector<std::string> art = monsters[0]->getArt();

	 for (int i = 0; i < (int)art.size(); i++)
	 {
		 setCursor(RIGHT_COL, LOG_START_ROW+i);
		 std::cout << art[i];
	 }

	for (int i = 0; i < (int)monsters.size(); ++i)
	{
		setCursor(RIGHT_COL, LOG_START_ROW + 16 + (4 * i));

		if (monsters[0]->isBoss())
			std::cout << monsters[i]->getName();
		else
			std::cout << i + 1 << ". " << monsters[i]->getName();

		int hpBar = (monsters[i]->getCurHp() * 30) / monsters[i]->getMaxHp();
		setCursor(RIGHT_COL, LOG_START_ROW + 16 + (4 * i) + 2);
		//std::cout << "체력: ";
		for (int j = 1; j <= 30; ++j)
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

	resetColor();
}

 void UIRenderer::printItemInfo(const std::vector<std::pair<std::string, int>>& itemList)
{
	for (int i = 0; i < (int)itemList.size(); ++i)
	{
		ItemData data = DataManager::getInstance().getItemData(itemList[i].first);

		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i));
		std::cout << i + 1 << ". " << data.name << " : " << itemList[i].second << "개";
		setCursor(RIGHT_COL, LOG_START_ROW + (4 * i) + 1);
		std::cout << data.description;
	}
}


 void UIRenderer::printMapInfo(const Map& map)
{
	setCursor(RIGHT_COL, LOG_START_ROW + 1);
	setColor(Color::BWHITE);
	std::cout << map.getName();
	setColor(Color::WHITE);
	setCursor(RIGHT_COL, LOG_START_ROW + 3);
	std::cout << map.getDescription();
}

 void UIRenderer::printMiniMap(const Map& map)
{
	printMapInfo(map);

	int curX = map.getCurrentX();
	int curY = map.getCurrentY();
	auto& gird = map.getRoomGrid();

	int mapStartY = LOG_START_ROW + 5;

	for (int y = 0; y < 6; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			int px = RIGHT_COL + x * 6;
			int py = mapStartY + y * 3;

			if (!gird[y][x])
				continue;  // 빈 칸은 그냥 비움

			bool isCur = (x == curX && y == curY);
			std::string mid = isCur ? "│ ■│" : "│   │";

			setCursor(px, py);     std::cout << "┌───┐";
			setCursor(px, py + 1); std::cout << mid;
			setCursor(px, py + 2); std::cout << "└───┘";
		}
	}
}

 void UIRenderer::setCursor(int x, int y)
{
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UIRenderer::setColor(Color color)
 {
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
 }

void UIRenderer::resetColor()
 {
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 기본색
 }

#include "InventoryHandler.h"
#include "../entity/Player.h"
#include "../ui/UIRenderer.h"
#include "../data/DataManager.h"
#include "../input/InputHandler.h"
#include <string>
#include <vector>

bool InventoryHandler::handleInventory(Player& player)
{
	auto& inven = player.getInven();

	if (inven.empty())
	{
		UIRenderer::addLog("소지품이 없다.");
		return false;
	}

	// 아이템 목록 출력
	std::vector<std::string> itemChoices;
	std::vector<std::pair<std::string, int>> itemList;
	int count = 0;
	for (auto& e : inven)
	{
		itemList.push_back(e);
		ItemData data = DataManager::getInstance().getItemData(e.first);
		itemChoices.push_back(std::to_string(++count) + ". " + data.name);
	}
	itemChoices.push_back("0. 취소");

	UIRenderer::printInvenScreen(itemList, player, itemChoices);

	int input = InputHandler::getInt(0, count, [&]() {UIRenderer::printInvenScreen(itemList, player, itemChoices); });

	if (input == 0)
	{
		return false;
	}

	std::string selectedId = itemList[input - 1].first;
	player.useItem(selectedId);

	auto data = DataManager::getInstance().getItemData(selectedId);

	std::vector<LogSegment>log;
	log.push_back(LogSegment("[" + data.name + "]", Color::CYAN));
	log.push_back(LogSegment(" 을/를 사용했다.", Color::WHITE));
	UIRenderer::addLog(log);

	if (!data.useLog.empty())
	{
		std::vector<LogSegment>useLog;
		useLog.push_back(LogSegment(data.useLog, Color::CYAN));
		UIRenderer::addLog(useLog);
	}

	return true;
}

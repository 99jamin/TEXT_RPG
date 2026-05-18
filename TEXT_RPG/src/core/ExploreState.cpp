#include "ExploreState.h"
#include "GameManager.h"
#include "CombatState.h"
#include "EndingState.h"
#include "HiddenEndingState.h"
#include "../map/RoomType.h"
#include "../data/DataManager.h"
#include "../entity/Player.h"
#include "../ui/UIRenderer.h"
#include "../save/SaveManager.h"
#include "../input/InputHandler.h"
#include "../sound/SoundManager.h"
#include <iostream>
#include <memory>

ExploreState::ExploreState(const std::string& mapId, bool isLoad)
    : m_map(DataManager::getInstance().getMapData(mapId))
{
    if (isLoad)
    {
        auto& mapData = SaveManager::getInstance().getMapData();
        m_map.loadFromSave(mapData.currentX, mapData.currentY, mapData.mapClearData.count(mapId) ? mapData.mapClearData.at(mapId) : std::vector<std::string>{});
    }
}

void ExploreState::enter(GameManager& manager)
{
    printRoomText();
    SoundManager::play(m_map.getBgm());
}

void ExploreState::update(GameManager& manager)
{
    UIRenderer::printExploreScreen(m_map, manager.getPlayer(), getChoices());

    int input = InputHandler::getInt(0, 4, [&]() {UIRenderer::printExploreScreen(m_map, manager.getPlayer(), getChoices()); });

    switch (input)
    {
    case 1: handleMove(manager); break;
    case 2: handleAction(manager); break;
    case 3: handleInventory(manager); break;
    case 4: handleDiary(manager); break;
    case 0: manager.quit(); break;
    }
}

 void ExploreState::exit(GameManager& manager) 
 {
     SoundManager::stop();
 }

 void ExploreState::pause(GameManager& manager) 
 {
     SoundManager::stop();
 }

 void ExploreState::resume(GameManager& manager) 
 {
     SoundManager::play(m_map.getBgm());
 }

// 현재 방 텍스트 출력
void ExploreState::printRoomText()
{
    Room* room = m_map.getCurRoom();
    if (!room->getText().empty())
    {
        if (room->getRoomType() == RoomType::Combat || room->getRoomType() == RoomType::Boss)
            printMonsterText(room);

        UIRenderer::addLog(room->getText());
    }
}

void ExploreState::printMonsterText(Room* room)
{
    if (room->isCleared())
        return;

    auto data = DataManager::getInstance().getMonsterData(room->getMonsterId());

    std::vector<LogSegment>log;
    log.push_back(LogSegment("[" + data.name + "]", Color::RED));
    log.push_back(LogSegment(" 와 조우했다.", Color::WHITE));
    UIRenderer::addLog(log);
}

std::vector<std::string> ExploreState::getChoices()
{
    Room* room = m_map.getCurRoom();

    std::vector<std::string> choices;
    choices.push_back("1. 이동하기");

    // 방 타입에 따라 2번 선택지 변경

    if (room->getRoomType() == RoomType::Exit)
    {
        if(m_map.getId()=="ending")
            choices.push_back("2. 자결한다");
        else
            choices.push_back("2. 다음 지역으로 이동하기");
    }
    else if ((room->getRoomType() == RoomType::Combat || room->getRoomType() == RoomType::Boss) && !room->isCleared())
        choices.push_back("2. 공격하기");
    else
        choices.push_back("2. 조사하기");

    choices.push_back("3. 소지품");
    choices.push_back("4. 일기");
    choices.push_back("0. 종료");

    return choices;
}

// 이동 처리
void ExploreState::handleMove(GameManager& manager)
{
    std::vector<std::string> choices;

    std::vector<Direction> availableDirs;
    if (m_map.canMove(Direction::North)) availableDirs.push_back(Direction::North);
    if (m_map.canMove(Direction::South)) availableDirs.push_back(Direction::South);
    if (m_map.canMove(Direction::West)) availableDirs.push_back(Direction::West);
    if (m_map.canMove(Direction::East)) availableDirs.push_back(Direction::East);

    Room* curRoom = m_map.getCurRoom();
    if (curRoom->getRoomType() == RoomType::Boss && !curRoom->isCleared())
    {
        availableDirs.erase(
            std::remove_if(availableDirs.begin(), availableDirs.end(),
                [&](Direction dir) {
                    Room* adj = m_map.getAdjacentRoom(dir);
                    return adj && adj->getRoomType() == RoomType::Exit;
                }),
            availableDirs.end()
        );
    }

    for (size_t i = 0; i < availableDirs.size(); i++)
        choices.push_back(std::to_string(i + 1) + "." + dirToString(availableDirs[i]));
    choices.push_back("0. 취소");

    UIRenderer::printExploreScreen(m_map, manager.getPlayer(), choices);

    int input = InputHandler::getInt(0, (int)availableDirs.size(), [&]() {UIRenderer::printExploreScreen(m_map, manager.getPlayer(), choices); });

    if (input == 0) return;

    Direction selected = availableDirs[input - 1];
    m_map.move(selected);
    printRoomText();
}

// 조사하기 / 공격하기 처리
void ExploreState::handleAction(GameManager& manager)
{
    Room* room = m_map.getCurRoom();

    if (room->isCleared())
    {
        UIRenderer::addLog("더 조사할 것은 없어보인다.");
        return;
    }

    switch (room->getRoomType())
    {
    case RoomType::Start:
    {
        UIRenderer::addLog(room->getActionText());
        break;
    }
    case RoomType::Combat:
    case RoomType::Boss:
    {
        manager.pushState(std::make_unique<CombatState>(room->getMonsterCount(), room->getMonsterId(), [room, &manager](CombatResult result)
            {
                if (result == CombatResult::Victory)
                {
                    room->setCleared();

                    UIRenderer::addLog("역귀를 처치했다.");

                    auto data = DataManager::getInstance().getMonsterData(room->getMonsterId());
                    if (!data.dropItemId.empty())
                    {
                        manager.getPlayer().addItem(data.dropItemId, 1);
                        ItemData itemData = DataManager::getInstance().getItemData(data.dropItemId);
                        std::vector<LogSegment>log;
                        log.push_back(LogSegment("[" + itemData.name + "]", Color::CYAN));
                        log.push_back(LogSegment(" 을/를 1 개 습득했다.", Color::WHITE));
                        UIRenderer::addLog(log);
                    }
                }
            }));
        break;
    }
    case RoomType::Item:
    {
        UIRenderer::addLog(room->getActionText());

        manager.getPlayer().addItem(room->getItemId(), room->getItemCount());

        std::vector<LogSegment>log;
        ItemData itemData = DataManager::getInstance().getItemData(room->getItemId());
        log.push_back(LogSegment("[" + itemData.name + "]", Color::CYAN));
        log.push_back(LogSegment(" 을/를" + std::to_string(room->getItemCount()) + " 개 습득했다.", Color::WHITE));
        UIRenderer::addLog(log);

        room->setCleared();

        break;
    }
    case RoomType::Event:
    {
        UIRenderer::addLog(room->getActionText());
        break;
    }
    case RoomType::Exit:
    {
        if (m_map.getId() == "ending")
        {
            if(manager.getPlayer().getFleshCount() >= 25)
                manager.pushState(std::make_unique<HiddenEndingState>());
            else
                manager.pushState(std::make_unique<EndingState>());
            break;
        }
        else
        {
            UIRenderer::addLog(room->getActionText());
            auto oldBgm = m_map.getBgm();

            m_map = Map(DataManager::getInstance().getMapData(m_map.getNextMapId()));

            if (oldBgm != m_map.getBgm())
            {
                SoundManager::stop();
                SoundManager::play(m_map.getBgm());
            }

            printRoomText();
            break;
        }
    }
    default:
        break;
    }
}

// 소지품 처리
void ExploreState::handleInventory(GameManager& manager)
{
    auto& inven = manager.getPlayer().getInven();

    if (inven.empty())
    {
        UIRenderer::addLog("소지품이 없다.");
        return;
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

    UIRenderer::printInvenScreen(itemList, manager.getPlayer(), itemChoices);

    int input = InputHandler::getInt(0, itemList.size(), [&]() {UIRenderer::printInvenScreen(itemList, manager.getPlayer(), itemChoices); });

    if (input == 0)
        return;

    std::string selectedId = itemList[input - 1].first;
    manager.getPlayer().useItem(selectedId);
    
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

}

// 일기 처리
void ExploreState::handleDiary(GameManager& manager)
{
    UIRenderer::printExploreScreen(m_map, manager.getPlayer(), { "1. 일기를 작성한다.","0. 취소" });

    int input = InputHandler::getInt(0, 1, [&]() {UIRenderer::printExploreScreen(m_map, manager.getPlayer(), { "1. 일기를 작성한다.","0. 취소" }); });

    if (input == 1)
    {
        UIRenderer::addLog("일기를 작성했다.");
        SaveManager::getInstance().saveData(manager.getPlayer(), m_map);
    }
}

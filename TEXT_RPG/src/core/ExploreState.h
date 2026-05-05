#pragma once
#include "GameState.h"
#include "GameManager.h"
#include "CombatState.h"
#include "../map/Map.h"
#include "../map/RoomType.h"
#include "../data/DataManager.h"
#include "../entity/Player.h"
#include "../ui/UIRenderer.h"
#include <iostream>
#include <memory>

class GameManager;

class ExploreState : public GameState
{
public:
    ExploreState(const std::string& mapId)
        : m_map(DataManager::getInstance().getMapData(mapId))
    {

    }

    void enter(GameManager& manager) override
    {
        printRoomText();
    }

    void update(GameManager& manager) override
    {
        UIRenderer::printExploreScreen(m_map, manager.getPlayer(), getChoices());

        int input;
        std::cin >> input;

        switch (input)
        {
        case 1: handleMove(manager); break;
        case 2: handleAction(manager); break;
        case 3: handleInventory(manager); break;
        case 4: handleDiary(manager); break;
        default: UIRenderer::addLog("잘못된 입력입니다."); break;
        }
    }

    void exit(GameManager& manager) override
    {
        // TODO: 세이브 처리
    }

private:

    // 현재 방 텍스트 출력
    void printRoomText()
    {
        Room* room = m_map.getCurRoom();
        if (!room->getText().empty())
            UIRenderer::addLog(room->getText());
    }

    // 선택지 출력
   
    std::vector<std::string> getChoices()
    {
        Room* room = m_map.getCurRoom();

        std::vector<std::string> choices;
        choices.push_back("1. 이동하기");

        // 방 타입에 따라 2번 선택지 변경
        if (room->getRoomType() == RoomType::Combat && !room->isCleared())
            choices.push_back("2. 공격하기");
        else
            choices.push_back("2. 조사하기");

        choices.push_back("3. 소지품");
        choices.push_back("4. 일기");

        return choices;
    }

    // 이동 처리
    void handleMove(GameManager& manager)
    {
        std::vector<std::string> choices;

        std::vector<Direction> availableDirs;
        if (m_map.canMove(Direction::North)) availableDirs.push_back(Direction::North);
        if (m_map.canMove(Direction::South)) availableDirs.push_back(Direction::South);
        if (m_map.canMove(Direction::West)) availableDirs.push_back(Direction::West);
        if (m_map.canMove(Direction::East)) availableDirs.push_back(Direction::East);

        for (int i = 0; i < availableDirs.size(); i++)
            choices.push_back(std::to_string(i + 1) + "." + dirToString(availableDirs[i]));
        choices.push_back("0. 취소");

        UIRenderer::printExploreScreen(m_map, manager.getPlayer(), choices);

        int input;
        std::cin >> input;

        if (input == 0) return;

        if (input < 1 || input >(int)availableDirs.size()) 
        {
            UIRenderer::addLog("잘못된 입력입니다.");
            return;
        }
        else 
        {
            Direction selected = availableDirs[input - 1];
            m_map.move(selected);
            printRoomText();
        }
    }

    // 조사하기 / 공격하기 처리
    void handleAction(GameManager& manager)
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
        {
            // TODO: CombatState로 전환
            manager.pushState(std::make_unique<CombatState>(room->getMonsterCount(), room->getMonsterId(), [room](CombatResult result) {
                if (result == CombatResult::Victory)
                    room->setCleared();
                }));
            break;
        }
        case RoomType::Item:
        {
            UIRenderer::addLog(room->getActionText());

            manager.getPlayer().addItem(room->getItemId(), room->getItemCount());

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
            UIRenderer::addLog(room->getActionText());

            m_map = Map(DataManager::getInstance().getMapData(m_map.getNextMapId()));
            printRoomText();
            break;
        }
        default:
            break;
        }
    }

    // 소지품 처리
    void handleInventory(GameManager& manager)
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
        itemChoices.push_back(std::to_string(++count) + ". 취소");

        UIRenderer::printInvenScreen(itemList, manager.getPlayer(), itemChoices);

        int input;
        std::cin >> input;

        if (input == count) return; // 취소
        if (input < 1 || input >= count)
        {
            UIRenderer::addLog("잘못된 선택입니다.");
            return;
        }

        std::string selectedId = itemList[input - 1].first;
        manager.getPlayer().useItem(selectedId);
    }
    
    // 일기 처리
    void handleDiary(GameManager& manager)
    {
        // TODO: DiaryState push
        UIRenderer::addLog("[일기 - 미구현]");
    }

    Map m_map;

};
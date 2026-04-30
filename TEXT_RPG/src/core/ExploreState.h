#pragma once
#include "GameState.h"
#include "GameManager.h"
#include "../map/Map.h"
#include "../map/RoomType.h"
#include "../data/DataManager.h"
#include "../entity/Player.h"
#include <iostream>

class GameManager;

class ExploreState : public GameState
{
public:
    ExploreState(const std::string& mapId, Player& player)
        : m_map(DataManager::getInstance().getMapData(mapId)), m_player(player)
    {

    }

    void enter(GameManager& manager) override
    {
        printMapText();
    }

    void update(GameManager& manager) override
    {
        printMenu();

        int input;
        std::cin >> input;

        switch (input)
        {
        case 1: handleMove(manager); break;
        case 2: handleAction(manager); break;
        case 3: handleInventory(manager); break;
        case 4: handleDiary(manager); break;
        default: std::cout << "잘못된 입력입니다.\n"; break;
        }
    }

    void exit(GameManager& manager) override
    {
        // TODO: 세이브 처리
    }

private:

    void printMapText()
    {
        std::cout << "\n[ " << m_map.getName() << " ]\n";
        std::cout << m_map.getDescription() << "\n";
        printRoomText();
    }

    // 현재 방 텍스트 출력
    void printRoomText()
    {
        Room* room = m_map.getCurRoom();
        if (!room->getText().empty())
            std::cout << "\n" << room->getText() << "\n";
    }

    // 선택지 출력
    void printMenu()
    {
        Room* room = m_map.getCurRoom();
        std::cout << "\n";

        std::cout << "1. 이동하기\n";

        // 방 타입에 따라 2번 선택지 변경
        if (room->getRoomType() == RoomType::Combat)
            std::cout << "2. 공격하기\n";
        else
            std::cout << "2. 조사하기\n";

        std::cout << "3. 소지품\n";
        std::cout << "4. 일기\n";
        std::cout << "> ";
    }

    // 이동 처리
    void handleMove(GameManager& manager)
    {
        std::vector<Direction> availableDirs;
        if (m_map.canMove(Direction::North)) availableDirs.push_back(Direction::North);
        if (m_map.canMove(Direction::South)) availableDirs.push_back(Direction::South);
        if (m_map.canMove(Direction::West)) availableDirs.push_back(Direction::West);
        if (m_map.canMove(Direction::East)) availableDirs.push_back(Direction::East);

        for (int i = 0; i < availableDirs.size(); i++)
            std::cout << i + 1 << "." << dirToString(availableDirs[i]) << "\n";
        std::cout << "0. 취소\n";

        int input;
        std::cin >> input;

        if (input == 0) return;

        if (input < 1 || input >(int)availableDirs.size()) 
        {
            std::cout << "잘못된 입력입니다.\n";
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

        switch (room->getRoomType())
        {
        case RoomType::Combat:
        {
            // TODO: CombatState로 전환
           /* MonsterData data = DataManager::getInstance().getMonsterData(room->getMonsterId());
            Monster* monster = new Monster(data);*/
            //manager.pushState(std::make_unique<CombatState>(m_player, monster));
            std::cout << "[전투 시작 - 미구현]\n";
            break;
        }
        case RoomType::Item:
        {
            std::cout << room->getActionText() << "\n";
            // TODO: 아이템 획득 처리
            m_player.addItem(room->getItemId(),room->getItemCount());
            break;
        }
        case RoomType::Event:
        {
            std::cout << room->getActionText() << "\n";
            break;
        }
        case RoomType::Exit:
        {
            std::cout << room->getActionText() << "\n";
            // TODO: 다음 맵으로 전환
            m_map = Map(DataManager::getInstance().getMapData(m_map.getNextMapId()));
            printMapText();
            break;
        }
        default:
            break;
        }
    }

    // 소지품 처리
    void handleInventory(GameManager& manager)
    {
        // TODO: InventoryState push
        std::cout << "[소지품 - 미구현]\n";
    }

    // 일기 처리
    void handleDiary(GameManager& manager)
    {
        // TODO: DiaryState push
        std::cout << "[일기 - 미구현]\n";
    }

    Map m_map;
    Player& m_player;
};
#pragma once
#include "GameState.h"
#include <vector>
#include "../combat/CombatResult.h"
#include "../map/Map.h"

class Room;
class Player;   
class Monster;  
class GameManager;

class ExploreState : public GameState
{
public:
    ExploreState(const std::string& mapId, bool isLoad = false);

    void enter(GameManager& manager) override;

    void update(GameManager& manager) override;

    void exit(GameManager& manager) override;

    void pause(GameManager& manager) override;

    void resume(GameManager& manager) override;

private:

    // 현재 방 텍스트 출력
    void printRoomText();

    void printMonsterText(Room* room);

    // 선택지 출력
    std::vector<std::string> getChoices();

    // 이동 처리
    void handleMove(GameManager& manager);

    // 조사하기 / 공격하기 처리
    void handleAction(GameManager& manager);

    // 소지품 처리
    void handleInventory(GameManager& manager);
    
    // 일기 처리
    void handleDiary(GameManager& manager);

    Map m_map;

};
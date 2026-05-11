#pragma once
#include "../data/DataTypes.h"
#include "Room.h"
#include "RoomType.h"
#include "Direction.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class Map
{
public:
    Map(const MapData& data);

    void loadFromSave(int currentX, int currentY, std::vector<std::string> clearRoomId);

    // 이동 시도 - 성공하면 true 반환
    bool move(Direction dir);

    // 이동 가능 여부 확인
    bool canMove(Direction dir) const;

    Room* getAdjacentRoom(Direction dir) const;

    Room* getCurRoom() const { return currentRoom; }

    const std::string& getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    const std::string& getDescription() const { return m_description; }
    const std::string& getNextMapId() const { return m_nextMapId; }
    std::vector<std::string> getClearRooms() const;

    // 미니맵 출력용
    const std::vector<std::vector<std::unique_ptr<Room>>>& getRoomGrid() const { return m_roomGrid; }
    int getCurrentX() const { return m_currentX; }
    int getCurrentY() const { return m_currentY; }

private:
    std::string m_id;
    std::string m_name;
    std::string m_description;
    std::string m_nextMapId;

    std::vector<std::vector<std::unique_ptr<Room>>> m_roomGrid;
    Room* currentRoom = nullptr;

    int m_currentX = 0;
    int m_currentY = 0;

    std::pair<int, int> getDelta(Direction dir) const;
};
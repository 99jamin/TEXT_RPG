#include "Map.h"
#include <memory>


Map::Map(const MapData& data)
    : m_id(data.id), m_name(data.name), m_description(data.description), m_nextMapId(data.nextMapId)
{
    // 6x6 grid Room 객체 생성
    m_roomGrid.resize(6);
    for (auto& row : m_roomGrid)
        row.resize(6);

    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            const std::string& roomId = data.grid[y][x];
            if (roomId.empty()) continue;

            auto it = data.rooms.find(roomId);
            if (it != data.rooms.end())
            {
                m_roomGrid[y][x] = std::make_unique<Room>(it->second);

                // start 방 위치 기억
                if (it->second.type == RoomType::Start)
                {
                    m_currentX = x;
                    m_currentY = y;
                }
            }
        }
    }

    currentRoom = m_roomGrid[m_currentY][m_currentX].get();
}

void Map::loadFromSave(int currentX, int currentY, std::vector<std::string> clearRoomId)
{
    m_currentX = currentX;
    m_currentY = currentY;

    for (auto& row : m_roomGrid)
    {
        for (auto& room : row)
        {
            if (!room)
                continue;

            for (auto& id : clearRoomId)
            {
                if (room->getRoomId() == id)
                    room->setCleared();
            }
        }
    }

    currentRoom = m_roomGrid[m_currentY][m_currentX].get();
}

// 이동 시도 - 성공하면 true 반환
bool Map::move(Direction dir)
{
    if (!canMove(dir))
        return false;

    auto [dx, dy] = getDelta(dir);

    m_currentX += dx;
    m_currentY += dy;
    currentRoom = m_roomGrid[m_currentY][m_currentX].get();
    return true;
}

// 이동 가능 여부 확인
bool Map::canMove(Direction dir) const
{
    auto [dx, dy] = getDelta(dir);

    int newX = m_currentX + dx;
    int newY = m_currentY + dy;

    if (newX < 0 || newX >= 6 || newY < 0 || newY >= 6) return false;
    return m_roomGrid[newY][newX] != nullptr;
}

Room* Map::getAdjacentRoom(Direction dir) const
{
    auto [dx, dy] = getDelta(dir);
    int nx = m_currentX + dx;
    int ny = m_currentY + dy;
    if (nx < 0 || nx >= 6 || ny < 0 || ny >= 6) return nullptr;
    return m_roomGrid[ny][nx].get();
}

std::vector<std::string> Map::getClearRooms() const
{
    std::vector<std::string> clearRooms;

    for (auto& row : m_roomGrid)
    {
        for (auto& room : row)
        {
            if (!room)
            {
                continue;
            }
            else
            {
                if (room->isCleared())
                    clearRooms.push_back(room->getRoomId());
            }
        }
    }
    return clearRooms;
}

std::pair<int, int> Map::getDelta(Direction dir) const
{
    switch (dir)
    {
    case Direction::North: return { 0,-1 };
    case Direction::South: return { 0,1 };
    case Direction::West:  return { -1,0 };
    case Direction::East:  return { 1,0 };
    }
    return{ 0,0 };
}

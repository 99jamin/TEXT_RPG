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

// 이동 시도 - 성공하면 true 반환
bool Map::move(Direction dir)
{
    int newX = m_currentX;
    int newY = m_currentY;

    switch (dir)
    {
    case Direction::North: newY--; break;
    case Direction::South: newY++; break;
    case Direction::West:  newX--; break;
    case Direction::East:  newX++; break;
    }

    // 범위 체크
    if (newX < 0 || newX >= 6 || newY < 0 || newY >= 6) return false;

    // 방 존재 체크
    if (m_roomGrid[newY][newX] == nullptr) return false;

    m_currentX = newX;
    m_currentY = newY;
    currentRoom = m_roomGrid[m_currentY][m_currentX].get();
    return true;
}

// 이동 가능 여부 확인
bool Map::canMove(Direction dir) const
{
    int newX = m_currentX;
    int newY = m_currentY;

    switch (dir)
    {
    case Direction::North: newY--; break;
    case Direction::South: newY++; break;
    case Direction::West:  newX--; break;
    case Direction::East:  newX++; break;
    }

    if (newX < 0 || newX >= 6 || newY < 0 || newY >= 6) return false;
    return m_roomGrid[newY][newX] != nullptr;
}

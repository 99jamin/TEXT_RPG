#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "DataTypes.h"
#include "../entity/Monster.h"

class DataManager {
public:
    static DataManager& getInstance();

    void loadAll();

    MonsterData getMonsterData(const std::string& id);

    SkillData getSkillData(SkillType skill);

    ItemData getItemData(const std::string& id);

    MapData getMapData(const std::string& id);

    std::string getItemName(const std::string& id);

private:
    DataManager() = default;

    void loadMonsters(const std::string& path);
    
    void loadItems(const std::string& path);
    
    void loadSkills(const std::string& path);

    void loadMaps(const std::string& path);

    MonsterEffect stringToMonsterEffect(const std::string& str);

    ItemEffect stringToItemEffect(const std::string& str);

    SkillType stringToSkillType(const std::string& str);

    RoomType stringToRoomType(const std::string& str);

    std::unordered_map<std::string, MonsterData> m_monsterTable;
    std::unordered_map<std::string, ItemData> m_itemTable;
    std::unordered_map<std::string, SkillData> m_skillTable;
    std::unordered_map<std::string, MapData> m_mapTable;
};
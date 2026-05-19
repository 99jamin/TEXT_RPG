#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "DataTypes.h"

class DataManager {
public:
    static DataManager& getInstance();

    void loadAll();

    const MonsterData& getMonsterData(const std::string& id) const;

    const SkillData& getSkillData(SkillType skill) const;

    const ItemData& getItemData(const std::string& id) const;

    const MapData& getMapData(const std::string& id) const;

    const std::vector<PageData>& getPrologueData() const;

    const std::vector<PageData>& getEndingData() const;

    const std::vector<PageData>& getHiddenEndingData() const;

private:
    DataManager() = default;

    void loadMonsters(const std::string& path);
    
    void loadItems(const std::string& path);
    
    void loadSkills(const std::string& path);

    void loadMaps(const std::string& path);

    void loadPrologue(const std::string& path);

    void loadEnding(const std::string& path);

    void loadHiddenEnding(const std::string& path);

    MonsterEffect stringToMonsterEffect(const std::string& str);

    ItemEffect stringToItemEffect(const std::string& str);

    SkillType stringToSkillType(const std::string& str);

    RoomType stringToRoomType(const std::string& str);

    std::unordered_map<std::string, MonsterData> m_monsterTable;
    std::unordered_map<std::string, ItemData> m_itemTable;
    std::unordered_map<std::string, SkillData> m_skillTable;
    std::unordered_map<std::string, MapData> m_mapTable;
    std::vector<PageData> m_PrologueTable;
    std::vector<PageData> m_EndingTable;
    std::vector<PageData> m_HiddenEndingTable;
};
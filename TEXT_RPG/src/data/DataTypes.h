#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../combat/MonsterEffect.h"
#include "../combat/SkillType.h"
#include "../entity/ItemEffect.h"
#include "../map/RoomType.h"


struct MonsterData {
    std::string id;
    std::string name;
    std::string description;
    int hp;
    int attack;
    int defense;
    MonsterEffect effect;
    std::string dropItemId;
};

struct ItemData {
    std::string id;
    std::string name;
    std::string description;
    ItemEffect effect;
    SkillType skillId;
    int value;
};

struct RoomData {
    std::string id;
    RoomType type;
    std::string text;
    std::string actionText;
    std::string monsterId;
    std::string itemId;
    int itemCount = 0;
};

struct MapData {
    std::string id;
    std::string name;
    std::string description;
    std::string nextMapId;
    std::vector<std::vector<std::string>> grid;
    std::unordered_map<std::string, RoomData> rooms;  // id → RoomData
};

struct SkillData {
    std::string id;
    std::string name;
    float damage_ratio;
    int stamina_cost;
};

#pragma once
#include <string>
#include <vector>
#include "../combat/MonsterEffect.h"
#include "../combat/SkillType.h"
#include "../entity/ItemEffect.h"

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

struct MapData {
    std::string id;
    std::string name;
    std::string description;
    std::string next_map;
    //std::vector<Room>grid;
};

struct SkillData {
    std::string id;
    std::string name;
    float damage_ratio;
    int stamina_cost;
};

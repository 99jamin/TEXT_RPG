#pragma once
#include <string>
#include <vector>
#include <map>
#include "../combat/MonsterEffect.h"
#include "../combat/SkillType.h"
#include "../entity/ItemEffect.h"
#include "../map/RoomType.h"


struct MonsterData 
{
    std::string id;
    std::string name;
    std::string attackLog;
    std::string phaseTwoLog;
    std::string dropItemId;
    int hp;
    int attack;
    int defense;
    MonsterEffect effect;
    std::vector<std::string> art;
    std::vector<std::string> art2;
};

struct ItemData 
{
    std::string id;
    std::string name;
    std::string description;
    std::string useLog;
    ItemEffect effect;
    SkillType skillId;
    int value;
};

struct RoomData 
{
    std::string id;
    RoomType type;
    std::string text;
    std::string actionText;
    std::string monsterId;
    int monsterCount;
    std::string itemId;
    int itemCount = 0;
};

struct MapData
{
    std::string id;
    std::string name;
    std::string description;
    std::string nextMapId;
    std::string bgm;
    std::vector<std::vector<std::string>> grid;
    std::map<std::string, RoomData> rooms;  // id → RoomData
};

struct SkillData 
{
    std::string id;
    std::string name;
    float damage_ratio;
    int stamina_cost;
};


struct SaveData
{
    // player
    struct PlayerSaveData
    {
        int hp;
        int stamina;
        int atk;
        int def;
        int fleshCount;
        bool poisoned;
        std::map<std::string, int> inventory;
        std::vector<SkillType> skills;
    };

    // map
    struct MapSaveData
    {
        std::string currentMapId;
        int currentX;
        int currentY;
        std::map<std::string, std::vector<std::string>> mapClearData;
    };

    PlayerSaveData player;
    MapSaveData map;
};

struct PageData
{
    std::vector<std::string> art;
    std::vector<std::string> lines;
};

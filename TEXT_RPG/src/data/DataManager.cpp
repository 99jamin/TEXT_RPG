#include "DataManager.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

DataManager& DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

void DataManager::loadAll()
{
    loadMonsters("data/monsters.json");
    loadItems("data/items.json");
    loadSkills("data/skills.json");
}

MonsterData DataManager::getMonsterData(const std::string& id)
{
    auto it = m_monsterTable.find(id);
    if (it != m_monsterTable.end())
        return it->second;
    return MonsterData{};
}

SkillData DataManager::getSkillData(SkillType skill)
{
    auto it = m_skillTable.find(toString(skill));
    if (it != m_skillTable.end())
        return it->second;
    return SkillData{};
}

ItemData DataManager::getItemData(const std::string& id)
{
    auto it = m_itemTable.find(id);
    if (it != m_itemTable.end())
        return it->second;
    return ItemData{};
}

void DataManager::loadMonsters(const std::string& path)
{
    std::ifstream file(path);
    json data = json::parse(file);

    for (auto& j : data["monsters"]) {
        MonsterData monster;
        monster.id = j["id"];
        monster.name = j["name"];
        monster.description = j["description"];
        monster.hp = j["hp"];
        monster.attack = j["attack"];
        monster.defense = j["defense"];
        monster.effect = stringToMonsterEffect(j["effect"]);
        monster.dropItemId = j["drop_item"];

        m_monsterTable[monster.id] = monster;
    }
}

void DataManager::loadItems(const std::string& path)
{
    std::ifstream file(path);
    json data = json::parse(file);

    for (auto& j : data["items"])
    {
        ItemData item;
        item.id = j["id"];
        item.name = j["name"];
        item.description = j["description"];
        item.effect = stringToItemEffect(j["effect"]);
        item.value = j.value("value", 0);  

        if (item.effect == ItemEffect::SkillLearn)
            item.skillId = stringToSkillType(j["skill"]);
        else
            item.skillId = SkillType::Nuigyeol;  

        m_itemTable[item.id] = item;
    }
}

void DataManager::loadSkills(const std::string& path)
{
    std::ifstream file(path);
    json data = json::parse(file);

    for (auto& j : data["skills"])
    {
        SkillData skill;
        skill.id = j["id"];
        skill.name = j["name"];
        skill.damage_ratio = j["damage_ratio"];
        skill.stamina_cost = j["stamina_cost"];

        m_skillTable[skill.id] = skill;
    }
}

MonsterEffect DataManager::stringToMonsterEffect(const std::string& str)
{
    if (str == "Poison")       return MonsterEffect::Poison;
    if (str == "StaminaDrain") return MonsterEffect::StaminaDrain;
    if (str == "HighDamage")   return MonsterEffect::HighDamage;
    if (str == "HpAbsorb")     return MonsterEffect::HpAbsorb;
    if (str == "HpRegen")      return MonsterEffect::HpRegen;
    return MonsterEffect::None;
}

ItemEffect DataManager::stringToItemEffect(const std::string& str)
{
    if (str == "HpRestore")     return ItemEffect::HpRestore;
    if (str == "HpRestoreFull") return ItemEffect::HpRestoreFull;
    if (str == "CurePoison")    return ItemEffect::CurePoison;
    if (str == "StaminaRestore") return ItemEffect::StaminaRestore;
    if (str == "SkillLearn")    return ItemEffect::SkillLearn;
    return ItemEffect::None;
}

SkillType DataManager::stringToSkillType(const std::string& str)
{
    if (str == "Nuigyeol")   return SkillType::Nuigyeol;
    if (str == "Musuki")     return SkillType::Musuki;
    if (str == "Neoul")      return SkillType::Neoul;
    if (str == "Gumni")      return SkillType::Gumni;
    if (str == "Mulmaru")    return SkillType::Mulmaru;
    if (str == "Soroksorok") return SkillType::Soroksorok;
    return SkillType::Nuigyeol;
}

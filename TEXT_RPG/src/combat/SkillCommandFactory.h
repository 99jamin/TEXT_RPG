#pragma once
#include "SkillType.h"
#include "SkillCommand.h"
#include "NuigyeolCommand.h"
#include "MusukiCommand.h"
#include "NeoulCommand.h"
#include "GumniCommand.h"
#include "MulmaruCommand.h"
#include "SoroksorokCommand.h"
#include "../data/DataManager.h"
#include <memory>

inline std::unique_ptr<SkillCommand> createSkillCommand(SkillType type) {
    switch (type) {
    
    case SkillType::Nuigyeol:
        return std::make_unique<NuigyeolCommand>(DataManager::getInstance().getSkillData(type));
    
    case SkillType::Musuki:
        return std::make_unique<MusukiCommand>(DataManager::getInstance().getSkillData(type));
    
    case SkillType::Neoul:
        return std::make_unique<NeoulCommand>(DataManager::getInstance().getSkillData(type));
    
    case SkillType::Gumni:
        return std::make_unique<GumniCommand>(DataManager::getInstance().getSkillData(type));
    
    case SkillType::Mulmaru:
        return std::make_unique<MulmaruCommand>(DataManager::getInstance().getSkillData(type));
   
    case SkillType::Soroksorok:
        return std::make_unique<SoroksorokCommand>(DataManager::getInstance().getSkillData(type));
        
    default:
        return nullptr;
    }
}

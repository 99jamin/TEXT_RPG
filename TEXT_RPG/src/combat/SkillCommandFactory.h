#pragma once
#include "SkillType.h"
#include "SkillCommand.h"
#include "NuigyeolCommand.h"
#include "MusukiCommand.h"
#include "NeoulCommand.h"
#include "GumniCommand.h"
#include "MulmaruCommand.h"
#include "SoroksorokCommand.h"
#include <memory>

inline std::unique_ptr<SkillCommand> createSkillCommand(SkillType type) {
    switch (type) {
    
    case SkillType::Nuigyeol:
        return std::make_unique<NuigyeolCommand>("官村家府: 圎搬", 1.2f, 1);
    
    case SkillType::Musuki:
        return std::make_unique<MusukiCommand>("官村家府: 公荐扁", 0.7f, 1);
    
    case SkillType::Neoul:
        return std::make_unique<NeoulCommand>("官村家府: 呈匡", 1.2f, 2);
    
    case SkillType::Gumni:
        return std::make_unique<GumniCommand>("官村家府: 崩吹", 1.5f, 1);
    
    case SkillType::Mulmaru:
        return std::make_unique<MulmaruCommand>("官村家府: 拱付风", 2.0f, 3);
   
    case SkillType::Soroksorok:
        return std::make_unique<SoroksorokCommand>("磊厘家府: 家废家废", 0.0f, 5);
        
    defalult:
        return nullptr;
    }
}

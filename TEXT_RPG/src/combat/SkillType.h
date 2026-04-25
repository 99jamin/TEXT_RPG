#pragma once

enum class SkillType 
{
	Nuigyeol,    // 뉫결
	Musuki,      // 무수기
	Neoul,       // 너울
	Gumni,       // 굼뉘
	Mulmaru,     // 물마루
	Soroksorok   // 소록소록
};

inline std::string toString(SkillType type) {
    switch (type) {
    case SkillType::Nuigyeol:  return "바닷소리: 뉫결";
    case SkillType::Musuki:    return "바닷소리: 무수기";
    case SkillType::Neoul:     return "바닷소리: 너울";
    case SkillType::Gumni:     return "바닷소리: 굼뉘";
    case SkillType::Mulmaru:   return "바닷소리: 물마루";
    case SkillType::Soroksorok: return "자장소리: 소록소록";
    default: return "알 수 없음";
    }
}
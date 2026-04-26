#pragma once

enum class MonsterEffect
{
    None,
    Poison,        // 독 부여 (갯것)
    StaminaDrain,  // 기력 감소 (팔귀, 뻘귀)
    HighDamage,    // 높은 데미지 (수라어)
    HpAbsorb,      // HP 흡수 (동굴태충)
    HpRegen,       // HP 회복 (적살귀)
    //보스전용 상태이상
};

//string2Effect 함수

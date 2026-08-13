# Game Design Document (GDD)
### 프로젝트명 : 섬그늘

---

## 목차
1. [프로젝트 개요](#1-프로젝트-개요)
2. [스토리 & 세계관](#2-스토리--세계관)
3. [게임 구조](#3-게임-구조)
4. [게임 시스템](#4-게임-시스템)
5. [콘텐츠 명세](#5-콘텐츠-명세)
6. [기술 설계](#6-기술-설계)
7. [개발 일정](#7-개발-일정)

---

## 1. 프로젝트 개요

| 항목 | 내용 |
|---|---|
| 장르 | 텍스트 RPG |
| 플랫폼 | Windows (Console) |
| 개발 언어 | C++17 |
| 개발 환경 | Visual Studio 2022 |
| 버전 관리 | Git / GitHub |
| 외부 라이브러리 | nlohmann/json (JSON 파싱), Windows MCI (사운드) |

### 1.1 게임 소개
> 처용가와 섬집아기를 모티프로 한 한국 중세 다크 판타지 텍스트 RPG.  
> 역병으로 위협받는 아이를 지키기 위해, 이름 없는 어머니가 남편이 남긴 검과 무가서를 들고 싸워나가는 이야기.

### 1.2 핵심 기술 목표
- [x] FSM (유한 상태 머신) 기반 게임 흐름 제어 — 스택 FSM
- [x] 데이터 드리븐 설계 — JSON으로 몬스터/아이템/맵 분리
- [x] 커맨드 패턴 기반 전투 시스템
- [x] 상속/다형성 — Entity 계층 구조
- [x] 스마트 포인터를 활용한 메모리 관리
- [x] 파일 I/O 기반 세이브/로드 (JSON)

### 1.3 레퍼런스
- 처용가 (신라 헌강왕 대 향가)
- 섬집아기 (한국 전통 자장가)

---

## 2. 스토리 & 세계관

> 상세 세계관은 [WBD (World Building Document)](WBD.md) 참고

### 2.1 배경
신라를 모티프로 한 한국 중세 판타지.

처용은 역신을 물리쳤으나, 아내는 역병을 품은 아이를 낳고 죽는다. 처용은 그 아이를 심해에 봉인한다.
오랜 시간이 지나 처용은 새 아내와 아이를 얻고, 역신의 귀환에 대비해 바닷소리를 본뜬 검무를 만든다.
바다에 적조가 퍼지고 역신이 용궁에 강림하자 처용은 이를 막으러 떠난 뒤 돌아오지 않는다.

3년 뒤의 이야기다.

### 2.2 주인공
| 항목 | 내용 |
|---|---|
| 이름 | 없음 |
| 신분 | 처용의 아내 |
| 무기 | 처용이 남긴 검 |
| 능력 | 처용의 무가서(武歌書)를 해독해 바닷소리 검무를 익힘 |
| 동기 | 아이를 노리는 위협을 제거하고 아이에게 돌아가는 것 |

### 2.3 주요 등장인물 / 세력
| 이름 | 설명 |
|---|---|
| 저퀴(疫鬼) | 처용이 봉인한 역병의 아이. 처용의 전 아내가 역신과의 사이에서 낳은 존재 |
| 적갑신 | 적조에 변이된 대게. 포구를 장악한 중간 보스 |


### 2.4 진행 흐름

| 단계 | 맵 | 목표 |
|---|---|---|
| 도입 | 바닷가 마을 | 아이를 맡기고 출발, 무가서 획득 |
| 전개 | 갯벌 해안 ~ 황폐한 어촌 | 스킬 습득, 역병 확산 확인 |
| 중반 | 적조 뒤덮인 포구 | 적갑신 처치, 섬으로 가는 배 확보 |
| 후반 | 섬 외부 ~ 지하 1층 | 저퀴의 심부 접근 |
| 결말 | 저퀴의 심부 | 최종 보스전, 엔딩 분기 |

```

---

## 3. 게임 구조

### 3.1 맵 구성
```
[바닷가 마을] ──→ [갯벌 해안] ──→ [황폐한 어촌]
                                         │
                                  [적조 뒤덮인 포구] ← 보스: 적갑신
                                         │
                                  [안개 낀 섬 외부]
                                         │
                                  [섬 동굴 입구]
                                         │
                                  [섬 지하 1층]
                                         │
                                  [저퀴의 심부] ← 최종 보스: 저퀴
```

### 3.2 맵별 등장 몬스터
| 맵 | 등장 몬스터 |
|---|---|
| 바닷가 마을 | 역병 어부, 역병 들개 |
| 갯벌 해안 | 패귀, 적구인 |
| 황폐한 어촌 | 역병 갈매기, 역병 어부 |
| 적조 뒤덮인 포구 | 수라어, 적갑신 (보스) |
| 안개 낀 섬 외부 | 역병 갈매기, 수라어 |
| 섬 동굴 입구 | 동굴 태충, 적살귀 |
| 섬 지하 1층 | 육안귀, 적살귀 |
| 저퀴의 심부 | 저퀴 (최종 보스) |

### 3.3 게임 흐름 (FSM)
```
[TitleState]
    │
[PageState] (프롤로그)
    │
[ExploreState] ←─────────────────┐
    │                             │
    ├── 몬스터 조우 → [CombatState] ─┤ (승리/도주)
    │                              │ (패배 → GameOverState)
    ├── 소지품 열기 → 인벤토리 UI (ExploreState 내부)
    ├── 일기 열기  → 세이브/로드 (ExploreState 내부)
    └── 맵 클리어  → 다음 ExploreState
                         │
                    [PageState] (엔딩/히든엔딩)
```

### 3.4 화면 구성
| 상태 | 화면 |
|---|---|
| 탐험 | 스탯바 + 로그 + 6x6 미니맵 + 계층형 선택지 |
| 전투 | 스탯바 + 적 정보 + 전투 로그 + 스킬 선택지 |
| 소지품 | 아이템 목록 + 사용/돌아가기 |
| 일기 | 저장하기/불러오기/돌아가기 |
| 게임 오버 | 텍스트 + 타이틀로 복귀 |
| 엔딩 | 스토리 텍스트 |

### 3.5 선택지 구조
```
1. 이동하기 (갈 수 있는 방향만 출력)
   ㄴ 1.동  2.서  3.남  4.북  0.돌아가기

2. 조사하기 / 공격하기 (몬스터 유무에 따라 전환)

3. 소지품
   ㄴ 아이템 목록 → 사용/돌아가기

4. 일기
   ㄴ 1.저장하기  0.돌아가기
```

### 3.6 맵 구조
- 그리드 크기: 6x6
- 방 배치: 고정 배치 (JSON 데이터로 정의)
- 도망 시 재조우: 해당 방 재진입 시 몬스터 유지

---

## 4. 게임 시스템

### 4.1 전투 시스템

**기본 흐름**
```
공격하기 선택 → CombatState 진입
→ 플레이어 턴 (스킬 선택)
→ 몬스터 턴 (자동)
→ 패시브 효과 처리
→ 상태이상 처리
→ 전투 종료 판정
→ 승리 / 패배 / 도주
```

**기력 규칙**
| 규칙 | 내용 |
|---|---|
| 최대 기력 | 5 |
| 턴당 회복 | 1 |


### 4.2 스킬 (바닷소리 / 자장소리)
| 분류 | 이름 | 기력 소모 | 효과 | 습득 위치 |
|---|---|---|---|---|
| 바닷소리 | 뉫결 | 1 | 기본 단타, 안정적 데미지 | 바닷가 마을 (시작) |
| 바닷소리 | 무수기 | 1 | 2회 연속 타격 | 갯벌 해안 |
| 바닷소리 | 너울 | 2 | 전체 공격 (다중 적 대응) | 황폐한 어촌 |
| 바닷소리 | 굼뉘 | 1 | 1턴 기모으기 → 2턴 공격, 기모으기 중 피격 시 데미지 증폭 | 섬 동굴 입구 |
| 바닷소리 | 물마루 | 3 | 강화 단타 | 섬 지하 1층 |
| 자장소리 | 소록소록 | 5 | 저퀴 전용 피니셔. | 저퀴의 심부 |

### 4.3 상태이상
| 상태이상 | 효과 | 부여 몬스터 |
|---|---|---|
| 역병 | 매 턴 HP 감소 | 패귀 |
| 기력 감소 | 현재 기력 -1 | 적구인, 육안귀 |

### 4.4 플레이어 스탯
| 스탯 | 초기값 | 붉은 살점 섭취 시 |
|---|---|---|
| HP | 100 | +30 |
| 기력 | 5 | +0 |
| 공격력 | 15 | +3 |
| 방어력 | 0 | +1 |

### 4.5 아이템
| 아이템 | 효과 | 획득처 |
|---|---|---|
| 붉은 살점 | 공격력, 방어력 증가 | 몬스터 처치 후 드롭 |
| 약초 | HP 30 회복 | 맵 탐험 중 발견 |
| 영약 | HP 완전 회복 | 보스 처치 후 드롭 |
| 향낭 | 상태이상 해제 | 맵 탐험 중 발견 |
| 어포 | 기력 2 회복 | 맵 탐험 중 발견 |
|무가서| 바닷소리:뉫결 획득| 특정 위치 드롭|
|무가서의 찢긴 조각1~4|스킬 습득|특정 위치 드롭|

- 인벤토리 최대 슬롯: 10
- 같은 아이템 최대 소지: 5개

### 4.6 세이브 / 로드
- 세이브 시점: 일기에서 수동 저장
- 세이브 형식: JSON 단일 슬롯
- 저장 항목: 현재 맵, HP, 기력, 공격력, 방어력, 인벤토리, 습득 스킬 목록, 클리어 맵 목록
- 게임 오버 시: 타이틀로 복귀

---

## 5. 콘텐츠 명세

### 5.1 몬스터 목록 및 스탯
| 이름 | HP | 공격력 | 방어력 | 공격 효과 | 드롭 | 비고 |
|---|---|---|---|---|---|---|
| 역병 어부 | 30 | 8 | 3 | 없음 | 붉은 살점 | |
| 들개 | 25 | 10 | 1 | 없음 | 붉은 살점 |  |
| 패귀 | 55 | 14 | 6 | 역병 부여 | 붉은 살점 | |
| 적구인 | 50 | 12 | 5 | 기력 감소 | 붉은 살점 | |
| 역병 갈매기 | 45 | 16 | 4 | 없음 | 붉은 살점 | |
| 수라어 | 60 | 22 | 8 | 높은 데미지 | 어포 | |
| 인어 | 65 | 18 | 10 | 없음 | 붉은 살점 | |
| 동굴 태충 | 70 | 20 | 8 | HP 흡수 | 붉은 살점 | |
| 적살귀 | 110 | 22 | 12 | 매 턴 HP 회복 | 붉은 살점 | |
| 육안귀 | 90 | 24 | 20 | 기력 감소 | 붉은 살점 | |
| 적갑신 | 200 | 30 | 20 | 높은 데미지 | 영약 | 중간 보스 (페이즈 전환) |
| 저퀴 | 350 | 35 | 20 | 독 부여 | 없음 | 최종 보스 (페이즈 전환) |

### 5.2 JSON 데이터 구조 예시

**monsters.json**
```json
{
  "monsters": [
    {
      "id": "plague_fisherman",
      "name": "어부",
      "attackLog": "가 회칼로 긁는다.",
      "hp": 30,
      "attack": 8,
      "defense": 3,
      "effect": "None",
      "drop_item": "red_flesh",
      "art": ["(ASCII 아트 배열)"]
    }
  ]
}
```

**maps.json**
```json
{
  "maps": [
    {
      "id": "village",
      "name": "바닷가 마을",
      "description": "역병이 덮친 바닷가 마을.",
      "next_map": "tidal_flat",
      "bgm": "bgm/zone1.mp3",
      "grid": [
        [null, null, null, null, null, null],
        ["start", "skill_1", null, null, null, null],
        [null, "combat_1", "item_1", "combat_2", null, null],
        [null, null, "combat_3", "event_2", "exit", null],
        [null, null, null, null, null, null],
        [null, null, null, null, null, null]
      ],
      "rooms": {
        "start":    { "type": "Start", "text": "...", "action_text": "..." },
        "combat_1": { "type": "Combat", "text": "...", "monster": "plague_fisherman", "monster_count": 1 },
        "item_1":   { "type": "Item", "text": "...", "action_text": "...", "item": "herb", "count": 1 },
        "exit":     { "type": "Exit" }
      }
    }
  ]
}
```

---

## 6. 기술 설계

### 6.1 폴더 구조
```
TEXT_RPG/
├── src/
│   ├── core/          # GameManager, GameState, FSM States
│   ├── entity/        # Entity, Player, Monster, Boss
│   ├── combat/        # CombatSystem, Command 패턴, 스킬
│   ├── map/           # Map, Room, Direction
│   ├── data/          # DataManager, 데이터 구조체
│   ├── ui/            # UIRenderer, LogLine
│   ├── inven/         # InventoryHandler
│   ├── input/         # InputHandler
│   ├── save/          # SaveManager
│   └── sound/         # SoundManager
├── data/
│   ├── monsters.json
│   ├── items.json
│   ├── skills.json
│   ├── maps.json
│   ├── prologue.json
│   ├── ending.json
│   └── hiddenending.json
├── saves/
│   └── save.json
├── bgm/
└── docs/
    └── GDD.md
```

### 6.2 클래스 목록
| 레이어 | 클래스 | 역할 |
|---|---|---|
| Core | GameManager | 게임 루프, 스택 FSM 관리 |
| Core | GameState (abstract) | 상태 기반 클래스 (enter/update/exit/pause/resume) |
| Core | TitleState | 타이틀 화면 |
| Core | ExploreState | 탐험 상태 (이동, 조사, 인벤토리, 세이브) |
| Core | CombatState | 전투 상태 |
| Core | PageState | 범용 페이지 상태 (프롤로그/엔딩/히든엔딩 공용) |
| Core | GameOverState | 게임 오버 화면 |
| Entity | IDamageable (interface) | 피해 처리 인터페이스 |
| Entity | Entity (abstract) | 캐릭터 공통 기반 (HP, ATK, DEF) |
| Entity | Player | 기력·스킬·인벤토리·상태이상 관리 |
| Entity | Monster | 공격효과 보유, MonsterFactory로 생성 |
| Entity | Boss | Monster + Template Method 페이즈 전환 |
| Entity | JeokkwiBoss / JeokgapsinBoss | 보스별 페이즈 전환 구현 |
| Combat | PlayerCommand (abstract) | 플레이어 전투 행동 기반 |
| Combat | SkillCommand (abstract) | 스킬 공통 기반 |
| Combat | 구체 스킬 (Nuigyeol, Musuki 등) | 개별 스킬 구현 |
| Combat | DefendCommand | 방어 행동 (피해 반감) |
| Combat | FleeCommand | 도주 행동 |
| Combat | MonsterAtkCommand | 몬스터 공격 + 효과별 분기 |
| Combat | CombatSystem | 전투 루프 실행 |
| Combat | SkillCommandFactory | SkillType → 구체 Command 생성 |
| Combat | MonsterFactory | JSON 데이터 → Monster/Boss 생성 |
| Map | Map | 6x6 그리드, 이동 로직, 미니맵 |
| Map | Room | 방 타입·몬스터·아이템·이벤트 |
| Data | DataManager (Singleton) | JSON 파싱 총괄 |
| Data | DataTypes | MonsterData / ItemData / MapData / SkillData / PageData |
| System | SaveManager (Singleton) | JSON 세이브/로드 |
| System | SoundManager | BGM/SFX (Windows MCI) |
| UI | UIRenderer | 콘솔 화면 출력 (레이아웃, 미니맵, 로그) |
| UI | InputHandler | 사용자 입력 처리 |
| UI | InventoryHandler | 인벤토리 UI (탐험/전투 공용) |

### 6.3 사용 기술 및 선택 이유
| 기술 | 적용 위치 | 선택 이유 |
|---|---|---|
| 스택 FSM | 게임 흐름 | pushState/popState로 상태 전환 명확화, 이전 상태 복귀 자연스러움 |
| 커맨드 패턴 | 전투 행동 | 플레이어/몬스터 행동을 동일 인터페이스로 캡슐화 |
| 팩토리 패턴 | 몬스터/스킬 생성 | JSON 데이터 → 객체 생성 로직 분리 |
| 템플릿 메서드 패턴 | Boss 페이즈 전환 | 공통 전환 로직은 Boss가, 세부 연출은 서브클래스가 담당 |
| 데이터 드리븐 | 몬스터/아이템/맵/스킬 | 코드-데이터 분리, 기획 변경에 유연 |
| 상속/다형성 | Entity 계층 | IDamageable → Entity → Player/Monster → Boss |
| unique_ptr | GameState 스택, Room 그리드 | 소유권 명확화, 자동 메모리 해제 |
| std::function | PageState 종료 동작 | 람다로 종료 동작 주입 (프롤로그: popState, 엔딩: quit) |
| nlohmann/json | DataManager, SaveManager | 헤더 하나로 JSON 파싱/직렬화 |
| Windows MCI | SoundManager | 외부 의존성 없이 BGM/SFX 재생 |

---

## 7. 개발 일정

### 7.1 마일스톤
| 단계 | 목표 |
|---|---|
| M1 | 프로젝트 셋업, GameManager + FSM 뼈대 구현 |
| M2 | Entity 계층 구조 + 커맨드 패턴 전투 시스템 |
| M3 | 데이터 드리븐 (JSON 로드) + 몬스터 데이터 |
| M4 | Map + Room 구조 + 미니맵 출력 |
| M5 | 세이브/로드 + UIRenderer 완성 |
| M6 | 전체 맵 콘텐츠 + 밸런싱 + 마무리 |

### 7.2 벨로그 포스팅 계획
| 편 | 주제 |
|---|---|
| 1편 | 기획 & GDD 작성기 (왜 이 프로젝트인가, 기술 목표) |
| 2편 | 구조 설계 & 클래스 다이어그램 |
| 3편 | FSM 구현 (스택 FSM, 상태 전환) |
| 4편 | 전투 시스템 & 커맨드 패턴 |
| 5편 | 데이터 드리븐 설계 (JSON) |
| 6편 | 세이브/로드 시스템 |
| 7편 | 회고 & 트러블슈팅 |

---

> 이 문서는 개발 진행에 따라 지속적으로 업데이트됩니다.

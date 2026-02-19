# JoseonGTA UE5.3+ 초기 스캐폴딩

## 0) 아키텍처 요약 + 실행/검증 체크리스트
- **권위 분리**: 플레이어의 신분/명성/수배/세력 평판은 `AJoseonPlayerState`를 authoritative 데이터 소스로 두고, 캐릭터 컴포넌트(`USocialClassComponent`, `UWantedComponent`)는 동기화 캐시 역할만 수행한다.
- **전투/퀘스트/세이브 축**: 실시간 전투는 `UCombatComponent`, 서사 진행은 `UQuestManager`, 영속화는 `UJoseonSaveSubsystem`으로 분리해 상호 결합을 최소화했다.
- **AI 추적 축**: `AAIController_JoseonGuard`는 Perception 기반 상태 전환(추적→수색→순찰)을 BT 없이도 동작하도록 구성했고, BT 연동 시 사용할 키/태스크 샘플을 별도 제공했다.
- **UI 축**: UMG 에셋 없이도 동작 가능한 `UJoseonHUDViewModel` 기반 델리게이트 바인딩 구조를 적용했다.

### 컴파일 성공까지 체크리스트
1. UE5.3+에서 C++ 프로젝트로 `JoseonGTA` 모듈 등록.
2. `JoseonGTA.Build.cs` 의존성(Json/AIModule/UMG/NetCore) 반영 확인.
3. 프로젝트 파일 재생성 후 IDE에서 Build.
4. `Project Settings > Maps & Modes`에서 `AJoseonGameModeBase` 지정.
5. 플레이어 Pawn에 `AJoseonCharacterBase`, AI Pawn에 `AGuardCharacter` 지정.
6. PIE 2인 멀티플레이로 RepNotify/RPC 동작 검증.
7. 로그에서 `LogJoseon` 카테고리 메시지 확인.

## 1) 폴더 트리
```text
Source/JoseonGTA
├─ Core
├─ Characters
├─ AI
├─ World
├─ Systems
├─ UI
├─ Networking
└─ Data
Content/Quests
```

## 9) 네트워크 포인트 요약
- `AJoseonPlayerState`
  - Replicated/RepNotify: SocialClass, Reputation, WantedLevel, WantedHeat, FactionReps
  - Server RPC: `ServerSetSocialClass`, `ServerSetReputation`, `ServerAddWantedHeat`, `ServerSetWantedHeat`, `ServerSetFactionRep`, `ServerAddFactionRep`
- `UCombatComponent`
  - Server RPC: `ServerAttack`
  - Multicast: `MulticastPlayAttackFX`
- `UQuestManager`
  - Server RPC 예시: `ServerAdvanceQuest`

## 10) 에디터 적용 순서
1. **GameMode 바인딩**: `AJoseonGameModeBase`를 기본 모드로 지정.
2. **플레이어 설정**: 기본 Pawn을 `AJoseonCharacterBase`, Controller를 `AJoseonPlayerController`로 지정.
3. **UI 연결**: `AJoseonPlayerController::HUDWidgetClass`에 Widget Blueprint 지정 후, 위젯에서 `IJoseonWidgetBindable` 구현.
4. **AI 배치**: 레벨에 `AGuardCharacter` 배치, AI Controller Class를 `AAIController_JoseonGuard`로 지정.
5. **NavMesh**: `NavMeshBoundsVolume` 배치 후 빌드.
6. **퀘스트 데이터**: `Content/Quests/*.json` 경로로 샘플 파일 배치 후 `UQuestManager::LoadFromFile` 호출.
7. **세이브 검증**: `UJoseonSaveSubsystem`의 `SaveCurrentState/LoadCurrentState` 블루프린트 호출로 상태 복원 확인.
8. **World Partition/Data Layer 가이드 적용**:
   - Persistent 레벨: `L_Hanyang_Persistent`
   - DataLayer: `Market`, `Palace`, `RiverPort`, `Wall`, `GisaengStreet`
   - 각 지형/프롭/AI 스폰을 DataLayer로 분리해 스트리밍 단위 구성.

## 11) 향후 확장 로드맵
- **전투 고도화**: 애니메이션 몽타주 기반 콤보 프레임/가드 브레이크/패링 판정 분리.
- **AI 고도화**: 기본 상태 머신을 BT/EQS 기반으로 치환, 수배 레벨별 분대 전술 추가.
- **월드 고도화**: Data Layer별 LOD/HLOD 프로파일 튜닝, 이동 경로 기반 인구 시뮬레이션.
- **네트워크 고도화**: 대규모 오픈월드용 Relevancy/Replication Graph 최적화.

## 12) 코드 리뷰(현재 한계/리스크/다음 커밋 우선순위)
### 현재 구현 한계
- 전투 히트 판정은 단순 Trace 기반으로 피격 부위/프레임 정확도가 낮다.
- QuestManager는 서버 단일 소유 기준이며 클라이언트 미러링/동기화 세부 정책이 미완성이다.
- Guard AI는 기본 추적 상태 머신이며 다수 AI 협동 전술(포위, 측면 기동)이 없다.

### 리스크
- `PlayerState` 중심 권위 구조에서 캐릭터 교체/리스폰 시 컴포넌트 캐시 재동기화 누락 가능성.
- Save/Load 시점에 서버 RPC를 즉시 호출하므로 전용서버/지연 환경에서 동기화 타이밍 이슈 가능.
- FactionRep를 `TMap<EFaction,float>`로 직접 복제하므로 빈번 갱신 시 네트워크 비용 증가 가능.

### 다음 커밋 우선순위
1. 전투 판정을 `UAbilityTask` 혹은 몽타주 Notify 기반으로 이전.
2. 퀘스트 상태를 FastArraySerializer 기반으로 네트워크 최적화.
3. 수배 레벨 2~5의 실제 증원 스폰/기마대 이동 파라미터를 DataAsset화.
4. UI ViewModel에 Stat/Quest/Wanted의 배치 업데이트(throttling) 적용.

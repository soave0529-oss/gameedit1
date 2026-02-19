# World Partition / Data Layer 적용 가이드

- Persistent 레벨 이름: `L_Hanyang_Persistent`
- 권장 Data Layer:
  - `Market`
  - `Palace`
  - `RiverPort`
  - `Wall`
  - `GisaengStreet`

## 적용 절차
1. 월드 세팅에서 World Partition 활성화.
2. 각 구역 액터를 Data Layer별로 분리.
3. AI 스폰 포인트와 Quest 트리거를 Layer 단위로 그룹화.
4. 테스트 시 `Data Layer Outliner`에서 스트리밍 전환 확인.

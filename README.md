# 비주얼노벨 특화 노코드 게임 제작 웹앱 (MVP)

## 1) 기술 선택 이유 (10줄 이내)
1. React + TypeScript 조합으로 에디터 UI를 타입 안정적으로 구성합니다.
2. Zustand를 사용해 노드/프로젝트 상태를 간결하게 관리합니다.
3. PixiJS로 런타임 렌더링 성능과 2D 표현력을 확보합니다.
4. TailwindCSS로 빠른 UI 프로토타이핑 및 일관된 스타일을 제공합니다.
5. zod 스키마로 프로젝트/노드/세이브 데이터 검증을 통합합니다.
6. Editor/Runtime/Shared 패키지 분리로 유지보수성과 확장성을 높입니다.
7. Node.js + Express 구조를 준비해 v1 공유 기능 API 확장을 대비합니다.
8. 테스트는 vitest로 빠르게 실행하고 핵심 엔진/저장 로직을 보호합니다.
9. 로컬 저장(LocalStorage 추상화)으로 세이브/로드 MVP를 즉시 제공합니다.
10. 정적 Export 번들 생성으로 웹 배포 경로를 단순화합니다.

## 2) 모노레포 디렉토리 구조 (tree)
```text
.
├─ packages
│  ├─ editor
│  │  ├─ src
│  │  │  ├─ components
│  │  │  ├─ App.tsx
│  │  │  ├─ main.tsx
│  │  │  ├─ store.ts
│  │  │  └─ styles.css
│  │  ├─ index.html
│  │  ├─ package.json
│  │  └─ vite.config.ts
│  ├─ runtime
│  │  ├─ src
│  │  │  ├─ engine.ts
│  │  │  ├─ saveLoad.ts
│  │  │  ├─ gallery.ts
│  │  │  ├─ exporter.ts
│  │  │  └─ index.ts
│  │  └─ package.json
│  ├─ server
│  │  └─ src/index.ts
│  └─ shared
│     └─ src
│        ├─ schema.ts
│        ├─ dummyProject.ts
│        └─ index.ts
├─ tests
├─ CHANGELOG.md
└─ .github/pull_request_template.md
```

## 3) 핵심 TypeScript 스키마 코드
- `packages/shared/src/schema.ts` 참고.
- `Project`, `StoryNode`, `SaveSlot` 스키마를 zod로 검증합니다.

## 4) Runtime 엔진 핵심 코드
- `packages/runtime/src/engine.ts` 참고.
- 노드 타입 switch 실행, deterministic 분기, 변수/엔딩/CG 상태 갱신을 담당합니다.

## 5) 세이브/로드 로직 코드
- `packages/runtime/src/saveLoad.ts` 참고.
- 슬롯 1~5 저장/조회/목록 정렬을 지원합니다.

## 6) CG 갤러리 처리 코드
- `packages/runtime/src/gallery.ts` 참고.
- 해금된 CG만 unlocked=true 처리합니다.

## 7) Editor 주요 컴포넌트 코드
- `packages/editor/src/components/*` 참고.
- 에셋 패널, 스토리 리스트, 노드 인스펙터, Pixi 미리보기를 제공합니다.

## 8) 실행 방법
```bash
npm install
npm run test
npm run dev:editor
```

## 9) MVP 체크리스트 표
| 항목 | 상태 | 비고 |
|---|---|---|
| 프로젝트 스키마 버전 포함 | 완료 | `schemaVersion` 필드 제공 |
| 에셋 라이브러리 구조 | 완료 | 타입/메타데이터 모델 포함 |
| 시나리오 노드 실행 | 완료 | dialogue/choice/condition/setVariable/unlockCG/ending |
| 세이브/로드 슬롯 5개 | 완료 | 1~5 슬롯 로직 |
| CG 갤러리 해금 | 완료 | 중복 해금 방지 |
| Export 번들 생성 | 완료 | index/runtime/project 출력 |
| 더미 프로젝트(3분기+1엔딩+CG해금) | 완료 | `dummyProject.ts` |
| 테스트 5개 이상 | 완료 | 총 6개 테스트 |

## 10) CHANGELOG.md 예시 (한국어)
- 루트 `CHANGELOG.md` 파일 참고.

## 11) PR 템플릿 (한국어)
- `.github/pull_request_template.md` 파일 참고.

## 12) 코드 리뷰 예시 (한국어)
- 예시: "`engine.step`의 choice 처리에서 조건부 옵션 필터링이 빠져 있습니다. `condition`이 있는 옵션은 렌더 전에 미리 평가하도록 수정 부탁드립니다."

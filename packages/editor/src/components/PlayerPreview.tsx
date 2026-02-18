import { Stage, Container, Text } from '@pixi/react';

// 한국어: 에디터 내 플레이어 레이아웃 미리보기를 위한 최소 Pixi 컴포넌트
export function PlayerPreview() {
  return (
    <div className="p-3 border-t border-slate-700">
      <h2 className="font-bold mb-2">플레이어 미리보기</h2>
      <Stage width={480} height={270} options={{ backgroundColor: 0x111827 }}>
        <Container>
          <Text text="배경/캐릭터 레이어 미리보기" x={20} y={40} style={{ fill: 'white', fontSize: 16 }} />
          <Text text="대사 박스 영역" x={20} y={210} style={{ fill: 'white', fontSize: 14 }} />
        </Container>
      </Stage>
    </div>
  );
}

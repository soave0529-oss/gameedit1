import { describe, expect, it } from 'vitest';
import { dummyProject } from '../packages/shared/src/dummyProject';
import { VisualNovelEngine } from '../packages/runtime/src/engine';

describe('VisualNovelEngine', () => {
  it('초기 상태에서 첫 대사 노드를 반환한다', () => {
    const engine = new VisualNovelEngine(dummyProject);
    const view = engine.step();
    expect(view.kind).toBe('dialogue');
    expect(view.node.id).toBe('n1');
  });

  it('선택지 분기를 통해 setVariable 노드를 실행한다', () => {
    const engine = new VisualNovelEngine(dummyProject);
    engine.step();
    const choiceView = engine.advanceDialogue();
    expect(choiceView.kind).toBe('choice');
    const endingView = engine.step('c1');
    expect(endingView.kind).toBe('ending');
    expect(engine.state.variables.affinity).toBe(2);
  });

  it('CG 해금 노드는 중복 없이 CG를 해금한다', () => {
    const engine = new VisualNovelEngine(dummyProject);
    engine.step();
    engine.advanceDialogue();
    engine.step('c3');
    expect(engine.state.unlockedCGIds).toEqual(['cg_1']);
  });
});

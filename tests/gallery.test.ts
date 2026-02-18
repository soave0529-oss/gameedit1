import { describe, expect, it } from 'vitest';
import { dummyProject } from '../packages/shared/src/dummyProject';
import { buildGalleryView } from '../packages/runtime/src/gallery';

describe('gallery', () => {
  it('해금 여부를 기준으로 갤러리 아이템을 반환한다', () => {
    const gallery = buildGalleryView(dummyProject, ['cg_1']);
    expect(gallery[0].unlocked).toBe(true);
  });
});

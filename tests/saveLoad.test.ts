import { describe, expect, it } from 'vitest';
import { buildSaveSlot, listSaveSlots, loadFromLocal, saveToLocal } from '../packages/runtime/src/saveLoad';

class MemoryStorage implements Storage {
  private map = new Map<string, string>();
  length = 0;
  clear(): void { this.map.clear(); this.length = 0; }
  getItem(key: string): string | null { return this.map.get(key) ?? null; }
  key(index: number): string | null { return [...this.map.keys()][index] ?? null; }
  removeItem(key: string): void { this.map.delete(key); this.length = this.map.size; }
  setItem(key: string, value: string): void { this.map.set(key, value); this.length = this.map.size; }
}

describe('save/load', () => {
  it('세이브 슬롯을 저장하고 다시 불러온다', () => {
    const storage = new MemoryStorage();
    const slot = buildSaveSlot(1, {
      currentNodeId: 'n1',
      variables: { a: 1 },
      unlockedCGIds: ['cg_1'],
      endingHistory: []
    }, 'bg1', 120);
    saveToLocal(slot, storage);
    const loaded = loadFromLocal(1, storage);
    expect(loaded?.currentNodeId).toBe('n1');
    expect(loaded?.thumbnailAssetId).toBe('bg1');
  });

  it('최대 5개 슬롯 목록을 최신순으로 가져온다', () => {
    const storage = new MemoryStorage();
    const first = buildSaveSlot(1, { currentNodeId: 'a', variables: {}, unlockedCGIds: [], endingHistory: [] }, null, 1);
    const second = buildSaveSlot(2, { currentNodeId: 'b', variables: {}, unlockedCGIds: [], endingHistory: [] }, null, 2);
    saveToLocal(first, storage);
    saveToLocal(second, storage);
    const list = listSaveSlots(storage);
    expect(list.length).toBe(2);
    expect(list[0].slot).toBe(2);
  });
});

import type { SaveSlot } from '@vn/shared';
import { SaveSlotSchema } from '@vn/shared';
import type { RuntimeState } from './engine';

const prefix = 'vn_save_slot_';

export function buildSaveSlot(slot: number, state: RuntimeState, thumbnailAssetId: string | null, playedSeconds: number): SaveSlot {
  return SaveSlotSchema.parse({
    slot,
    thumbnailAssetId,
    currentNodeId: state.currentNodeId,
    variables: state.variables,
    unlockedCGIds: state.unlockedCGIds,
    playedSeconds,
    timestamp: Date.now()
  });
}

export function saveToLocal(slot: SaveSlot, storage: Storage = localStorage): void {
  storage.setItem(`${prefix}${slot.slot}`, JSON.stringify(slot));
}

export function loadFromLocal(slot: number, storage: Storage = localStorage): SaveSlot | null {
  const raw = storage.getItem(`${prefix}${slot}`);
  if (!raw) {
    return null;
  }
  return SaveSlotSchema.parse(JSON.parse(raw));
}

export function listSaveSlots(storage: Storage = localStorage): SaveSlot[] {
  const slots: SaveSlot[] = [];
  for (let i = 1; i <= 5; i += 1) {
    const found = loadFromLocal(i, storage);
    if (found) slots.push(found);
  }
  return slots.sort((a, b) => b.timestamp - a.timestamp);
}

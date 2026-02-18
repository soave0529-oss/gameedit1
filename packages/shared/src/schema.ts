import { z } from 'zod';

export const AssetTypeSchema = z.enum([
  'background',
  'character',
  'cg',
  'animation',
  'bgm',
  'se',
  'voice'
]);

export const AssetSchema = z.object({
  id: z.string(),
  type: AssetTypeSchema,
  path: z.string(),
  mimeType: z.string(),
  width: z.number().optional(),
  height: z.number().optional(),
  sizeBytes: z.number(),
  metadata: z.record(z.union([z.string(), z.number(), z.boolean()])).default({})
});

export const ConditionSchema = z.object({
  variable: z.string(),
  operator: z.enum(['==', '!=', '>', '>=', '<', '<=']),
  value: z.number()
});

export const ChoiceItemSchema = z.object({
  id: z.string(),
  text: z.string(),
  targetNodeId: z.string(),
  condition: ConditionSchema.optional()
});

const DialogueNodeDataSchema = z.object({
  speaker: z.string(),
  text: z.string(),
  autoType: z.boolean().default(true),
  voiceAssetId: z.string().optional(),
  backgroundAssetId: z.string().optional(),
  characterLayers: z.array(z.object({
    assetId: z.string(),
    position: z.enum(['left', 'center', 'right'])
  })).default([])
});

const ChoiceNodeDataSchema = z.object({
  options: z.array(ChoiceItemSchema).min(1)
});

const ConditionNodeDataSchema = z.object({
  condition: ConditionSchema,
  trueNodeId: z.string(),
  falseNodeId: z.string()
});

const SetVariableNodeDataSchema = z.object({
  variable: z.string(),
  operation: z.enum(['set', 'add', 'subtract']),
  value: z.number()
});

const UnlockCGNodeDataSchema = z.object({
  cgId: z.string()
});

const EndingNodeDataSchema = z.object({
  endingId: z.string(),
  title: z.string()
});

export const StoryNodeSchema = z.discriminatedUnion('type', [
  z.object({
    id: z.string(),
    type: z.literal('dialogue'),
    data: DialogueNodeDataSchema,
    nextNodeId: z.string().optional()
  }),
  z.object({
    id: z.string(),
    type: z.literal('choice'),
    data: ChoiceNodeDataSchema
  }),
  z.object({
    id: z.string(),
    type: z.literal('condition'),
    data: ConditionNodeDataSchema
  }),
  z.object({
    id: z.string(),
    type: z.literal('setVariable'),
    data: SetVariableNodeDataSchema,
    nextNodeId: z.string().optional()
  }),
  z.object({
    id: z.string(),
    type: z.literal('unlockCG'),
    data: UnlockCGNodeDataSchema,
    nextNodeId: z.string().optional()
  }),
  z.object({
    id: z.string(),
    type: z.literal('ending'),
    data: EndingNodeDataSchema
  })
]);

export const ProjectSchema = z.object({
  id: z.string(),
  name: z.string(),
  schemaVersion: z.string(),
  assets: z.array(AssetSchema),
  variablesGlobal: z.record(z.number()),
  storyNodes: z.array(StoryNodeSchema),
  cgGallery: z.array(z.object({
    id: z.string(),
    assetId: z.string(),
    title: z.string()
  })),
  endings: z.array(z.object({
    id: z.string(),
    title: z.string()
  })),
  startNodeId: z.string()
});

export type Project = z.infer<typeof ProjectSchema>;
export type StoryNode = z.infer<typeof StoryNodeSchema>;
export type Condition = z.infer<typeof ConditionSchema>;

export const SaveSlotSchema = z.object({
  slot: z.number().min(1).max(5),
  thumbnailAssetId: z.string().nullable(),
  currentNodeId: z.string(),
  variables: z.record(z.number()),
  unlockedCGIds: z.array(z.string()),
  playedSeconds: z.number(),
  timestamp: z.number()
});

export type SaveSlot = z.infer<typeof SaveSlotSchema>;

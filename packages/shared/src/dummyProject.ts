import type { Project } from './schema';

export const dummyProject: Project = {
  id: 'project-demo-1',
  name: '데모 비주얼노벨',
  schemaVersion: '1.0.0',
  startNodeId: 'n1',
  variablesGlobal: {
    affinity: 0
  },
  assets: [
    { id: 'bg_room', type: 'background', path: 'assets/bg_room.webp', mimeType: 'image/webp', width: 1280, height: 720, sizeBytes: 1024, metadata: {} },
    { id: 'cg_event_1', type: 'cg', path: 'assets/cg_event_1.webp', mimeType: 'image/webp', width: 1280, height: 720, sizeBytes: 1200, metadata: {} }
  ],
  cgGallery: [
    { id: 'cg_1', assetId: 'cg_event_1', title: '첫 만남 CG' }
  ],
  endings: [
    { id: 'ending_normal', title: '일상 엔딩' }
  ],
  storyNodes: [
    {
      id: 'n1',
      type: 'dialogue',
      data: {
        speaker: '주인공',
        text: '오늘은 어떤 선택을 할까?',
        autoType: true,
        backgroundAssetId: 'bg_room',
        characterLayers: []
      },
      nextNodeId: 'n2'
    },
    {
      id: 'n2',
      type: 'choice',
      data: {
        options: [
          { id: 'c1', text: '공부한다', targetNodeId: 'n3' },
          { id: 'c2', text: '쉰다', targetNodeId: 'n4' },
          { id: 'c3', text: '산책한다', targetNodeId: 'n5' }
        ]
      }
    },
    {
      id: 'n3',
      type: 'setVariable',
      data: { variable: 'affinity', operation: 'add', value: 2 },
      nextNodeId: 'n6'
    },
    {
      id: 'n4',
      type: 'setVariable',
      data: { variable: 'affinity', operation: 'add', value: 1 },
      nextNodeId: 'n6'
    },
    {
      id: 'n5',
      type: 'unlockCG',
      data: { cgId: 'cg_1' },
      nextNodeId: 'n6'
    },
    {
      id: 'n6',
      type: 'ending',
      data: { endingId: 'ending_normal', title: '일상 엔딩' }
    }
  ]
};

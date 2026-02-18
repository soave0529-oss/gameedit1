import { create } from 'zustand';
import type { Project, StoryNode } from '@vn/shared';
import { dummyProject } from '@vn/shared';

interface EditorState {
  project: Project;
  selectedNodeId: string;
  selectNode: (nodeId: string) => void;
  updateNode: (nodeId: string, updater: (node: StoryNode) => StoryNode) => void;
}

export const useEditorStore = create<EditorState>((set) => ({
  project: dummyProject,
  selectedNodeId: dummyProject.startNodeId,
  selectNode: (nodeId) => set({ selectedNodeId: nodeId }),
  updateNode: (nodeId, updater) =>
    set((state) => ({
      project: {
        ...state.project,
        storyNodes: state.project.storyNodes.map((node) => (node.id === nodeId ? updater(node) : node))
      }
    }))
}));

import type { Project, StoryNode } from '@vn/shared';

export interface RuntimeState {
  currentNodeId: string;
  variables: Record<string, number>;
  unlockedCGIds: string[];
  endingHistory: string[];
}

export interface DialogueView {
  kind: 'dialogue';
  node: Extract<StoryNode, { type: 'dialogue' }>;
}

export interface ChoiceView {
  kind: 'choice';
  node: Extract<StoryNode, { type: 'choice' }>;
}

export interface EndingView {
  kind: 'ending';
  node: Extract<StoryNode, { type: 'ending' }>;
}

export type RuntimeView = DialogueView | ChoiceView | EndingView;

export class VisualNovelEngine {
  private readonly nodeMap: Map<string, StoryNode>;
  public state: RuntimeState;

  constructor(private readonly project: Project) {
    this.nodeMap = new Map(project.storyNodes.map((node) => [node.id, node]));
    this.state = {
      currentNodeId: project.startNodeId,
      variables: { ...project.variablesGlobal },
      unlockedCGIds: [],
      endingHistory: []
    };
  }

  public getCurrentNode(): StoryNode {
    const node = this.nodeMap.get(this.state.currentNodeId);
    if (!node) {
      throw new Error(`노드를 찾을 수 없습니다: ${this.state.currentNodeId}`);
    }
    return node;
  }

  public step(choiceId?: string): RuntimeView {
    while (true) {
      const node = this.getCurrentNode();
      switch (node.type) {
        case 'dialogue':
          return { kind: 'dialogue', node };
        case 'choice': {
          if (!choiceId) {
            return { kind: 'choice', node };
          }
          const chosen = node.data.options.find((option) => option.id === choiceId);
          if (!chosen) {
            throw new Error(`선택지 ID가 유효하지 않습니다: ${choiceId}`);
          }
          this.state.currentNodeId = chosen.targetNodeId;
          choiceId = undefined;
          continue;
        }
        case 'condition': {
          const { condition, trueNodeId, falseNodeId } = node.data;
          const currentValue = this.state.variables[condition.variable] ?? 0;
          const success = evaluateCondition(currentValue, condition.operator, condition.value);
          this.state.currentNodeId = success ? trueNodeId : falseNodeId;
          continue;
        }
        case 'setVariable': {
          const before = this.state.variables[node.data.variable] ?? 0;
          if (node.data.operation === 'set') {
            this.state.variables[node.data.variable] = node.data.value;
          } else if (node.data.operation === 'add') {
            this.state.variables[node.data.variable] = before + node.data.value;
          } else {
            this.state.variables[node.data.variable] = before - node.data.value;
          }
          if (!node.nextNodeId) {
            throw new Error(`다음 노드가 설정되지 않았습니다: ${node.id}`);
          }
          this.state.currentNodeId = node.nextNodeId;
          continue;
        }
        case 'unlockCG': {
          if (!this.state.unlockedCGIds.includes(node.data.cgId)) {
            this.state.unlockedCGIds.push(node.data.cgId);
          }
          if (!node.nextNodeId) {
            throw new Error(`다음 노드가 설정되지 않았습니다: ${node.id}`);
          }
          this.state.currentNodeId = node.nextNodeId;
          continue;
        }
        case 'ending': {
          if (!this.state.endingHistory.includes(node.data.endingId)) {
            this.state.endingHistory.push(node.data.endingId);
          }
          return { kind: 'ending', node };
        }
      }
    }
  }

  public advanceDialogue(): RuntimeView {
    const node = this.getCurrentNode();
    if (node.type !== 'dialogue') {
      throw new Error('대사 노드가 아닙니다.');
    }
    if (!node.nextNodeId) {
      throw new Error(`다음 노드가 설정되지 않았습니다: ${node.id}`);
    }
    this.state.currentNodeId = node.nextNodeId;
    return this.step();
  }
}

function evaluateCondition(left: number, operator: string, right: number): boolean {
  switch (operator) {
    case '==':
      return left === right;
    case '!=':
      return left !== right;
    case '>':
      return left > right;
    case '>=':
      return left >= right;
    case '<':
      return left < right;
    case '<=':
      return left <= right;
    default:
      return false;
  }
}

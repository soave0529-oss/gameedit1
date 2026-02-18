import { useMemo } from 'react';
import { useEditorStore } from '../store';

export function NodeInspector() {
  const selectedNodeId = useEditorStore((state) => state.selectedNodeId);
  const node = useEditorStore((state) => state.project.storyNodes.find((item) => item.id === selectedNodeId));
  const updateNode = useEditorStore((state) => state.updateNode);

  const nodeSummary = useMemo(() => {
    if (!node) return '노드를 선택하세요.';
    if (node.type === 'dialogue') return node.data.text;
    if (node.type === 'choice') return `선택지 ${node.data.options.length}개`;
    if (node.type === 'ending') return node.data.title;
    return JSON.stringify(node.data);
  }, [node]);

  if (!node) {
    return <section className="p-3">노드가 없습니다.</section>;
  }

  return (
    <section className="p-3 space-y-2">
      <h2 className="font-bold">노드 상세</h2>
      <p className="text-sm text-slate-300">요약: {nodeSummary}</p>
      {node.type === 'dialogue' && (
        <textarea
          className="w-full h-32 bg-slate-900 rounded p-2"
          value={node.data.text}
          onChange={(event) => {
            const nextText = event.target.value;
            updateNode(node.id, (prevNode) => {
              if (prevNode.type !== 'dialogue') return prevNode;
              return {
                ...prevNode,
                data: {
                  ...prevNode.data,
                  text: nextText
                }
              };
            });
          }}
        />
      )}
    </section>
  );
}

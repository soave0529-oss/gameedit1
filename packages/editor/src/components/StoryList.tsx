import { useEditorStore } from '../store';

export function StoryList() {
  const nodes = useEditorStore((state) => state.project.storyNodes);
  const selectedNodeId = useEditorStore((state) => state.selectedNodeId);
  const selectNode = useEditorStore((state) => state.selectNode);

  return (
    <section className="p-3">
      <h2 className="font-bold mb-2">스토리 플로우</h2>
      <ul className="space-y-2">
        {nodes.map((node) => (
          <li key={node.id}>
            <button
              className={`w-full text-left rounded p-2 ${selectedNodeId === node.id ? 'bg-indigo-600' : 'bg-slate-800'}`}
              onClick={() => selectNode(node.id)}
            >
              {node.id} - {node.type}
            </button>
          </li>
        ))}
      </ul>
    </section>
  );
}

import { useEditorStore } from '../store';

export function AssetPanel() {
  const assets = useEditorStore((state) => state.project.assets);
  return (
    <section className="p-3 border-b border-slate-700">
      <h2 className="font-bold mb-2">에셋 패널</h2>
      <ul className="space-y-1 text-sm">
        {assets.map((asset) => (
          <li key={asset.id} className="bg-slate-800 rounded p-2">
            <p>{asset.id}</p>
            <p className="text-slate-400">{asset.type} / {asset.mimeType}</p>
          </li>
        ))}
      </ul>
    </section>
  );
}

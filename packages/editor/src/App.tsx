import { AssetPanel } from './components/AssetPanel';
import { StoryList } from './components/StoryList';
import { NodeInspector } from './components/NodeInspector';
import { PlayerPreview } from './components/PlayerPreview';

export default function App() {
  return (
    <main className="min-h-screen bg-slate-900 text-slate-100 grid grid-cols-[260px_1fr_340px]">
      <aside className="border-r border-slate-700">
        <AssetPanel />
      </aside>
      <section className="border-r border-slate-700 flex flex-col">
        <header className="p-3 border-b border-slate-700 flex gap-2">
          <button className="px-3 py-1 bg-emerald-600 rounded">Play</button>
          <button className="px-3 py-1 bg-blue-600 rounded">Save</button>
          <button className="px-3 py-1 bg-amber-600 rounded">Export</button>
        </header>
        <StoryList />
        <PlayerPreview />
      </section>
      <aside>
        <NodeInspector />
      </aside>
    </main>
  );
}

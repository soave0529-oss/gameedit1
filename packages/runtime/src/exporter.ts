import type { Project } from '@vn/shared';

export interface ExportBundle {
  'index.html': string;
  'runtime.js': string;
  'project.json': string;
}

// 한국어: 실제 zip 압축 전 단계로 정적 파일 내용을 생성합니다.
export function buildExportBundle(project: Project): ExportBundle {
  return {
    'index.html': `<!doctype html><html><head><meta charset="UTF-8" /><title>${project.name}</title></head><body><div id="app"></div><script src="runtime.js"></script></body></html>`,
    'runtime.js': `fetch('project.json').then(r=>r.json()).then(p=>{document.getElementById('app').innerText='프로젝트: '+p.name;});`,
    'project.json': JSON.stringify(project, null, 2)
  };
}

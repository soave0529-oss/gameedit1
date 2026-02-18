import type { Project } from '@vn/shared';

export interface GalleryItemView {
  id: string;
  title: string;
  assetId: string;
  unlocked: boolean;
}

export function buildGalleryView(project: Project, unlockedCGIds: string[]): GalleryItemView[] {
  return project.cgGallery.map((cg) => ({
    id: cg.id,
    title: cg.title,
    assetId: cg.assetId,
    unlocked: unlockedCGIds.includes(cg.id)
  }));
}

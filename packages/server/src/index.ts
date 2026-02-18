import express from 'express';

const app = express();
app.use(express.json());

// 한국어: v1 확장을 위해 프로젝트 메타데이터 API 골격만 우선 제공합니다.
app.get('/health', (_req, res) => {
  res.json({ ok: true, message: '서버 준비 완료' });
});

const port = Number(process.env.PORT ?? 4000);
app.listen(port, () => {
  console.log(`서버 실행 중: http://localhost:${port}`);
});

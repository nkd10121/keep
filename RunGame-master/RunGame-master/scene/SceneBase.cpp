#include "SceneBase.h"
#include "DxLib.h"
#include "game.h"
#include "Mouse.h"

#include <cassert>
#include "Player.h"
#include "Sound.h"

namespace
{
	// フェードにかかるフレームデフォルト
	constexpr int kFadeFrameDefault = 32;
//	constexpr int kFadeFrameDefault = 60 * 5;

	// マウスカーソルサイズ
	constexpr int kCursorSize = 32;

	// フェードカラー
	constexpr unsigned int kFadeColor[] =
	{
		// ちょっと暗め
		0xe06060,
		0xe060a0,
		0xe060e0,
		0xa060e0,
		0x6060e0,
		0x60a0e0,
		0x60e0e0,
		0x60e0a0,
		0x60e060,
		0xa0e060,
		0xe0e060,
		0xe0a060
	};
	constexpr int kFadeColorNum = _countof(kFadeColor);


	// 横方向のグラデーションの四角形を描画する
	void GradX_RGB(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
	{
		VERTEX2D Vertex[6];

		// 左上の頂点の情報をセット( 1ポリゴン目の第1頂点 )
		Vertex[0].pos.x = (float)x1;
		Vertex[0].pos.y = (float)y1;
		Vertex[0].pos.z = 0.0f;
		Vertex[0].rhw = 1.0f;
		Vertex[0].dif.r = r1;
		Vertex[0].dif.g = g1;
		Vertex[0].dif.b = b1;
		Vertex[0].dif.a = 255;
		Vertex[0].u = 0.0f;
		Vertex[0].v = 0.0f;

		// 右上の頂点の情報をセット( 1ポリゴン目の第2頂点 )
		Vertex[1].pos.x = (float)x2;
		Vertex[1].pos.y = (float)y1;
		Vertex[1].pos.z = 0.0f;
		Vertex[1].rhw = 1.0f;
		Vertex[1].dif.r = r1;
		Vertex[1].dif.g = g1;
		Vertex[1].dif.b = b1;
		Vertex[1].dif.a = 255;
		Vertex[1].u = 0.0f;
		Vertex[1].v = 0.0f;

		// 左下の頂点の情報をセット( 1ポリゴン目の第3頂点 )
		Vertex[2].pos.x = (float)x1;
		Vertex[2].pos.y = (float)y2;
		Vertex[2].pos.z = 0.0f;
		Vertex[2].rhw = 1.0f;
		Vertex[2].dif.r = r2;
		Vertex[2].dif.g = g2;
		Vertex[2].dif.b = b2;
		Vertex[2].dif.a = 255;
		Vertex[2].u = 0.0f;
		Vertex[2].v = 0.0f;

		// 右下の頂点の情報をセット( 2ポリゴン目の第1頂点 )
		Vertex[3].pos.x = (float)x2;
		Vertex[3].pos.y = (float)y2;
		Vertex[3].pos.z = 0.0f;
		Vertex[3].rhw = 1.0f;
		Vertex[3].dif.r = r2;
		Vertex[3].dif.g = g2;
		Vertex[3].dif.b = b2;
		Vertex[3].dif.a = 255;
		Vertex[3].u = 0.0f;
		Vertex[3].v = 0.0f;

		// 2ポリゴン目の第2頂点は左下の頂点なのでコピー
		Vertex[4] = Vertex[2];

		// 2ポリゴン目の第3頂点は右上の頂点なのでコピー
		Vertex[5] = Vertex[1];

		// ポリゴンを2個描画
		DrawPolygon2D(Vertex, 2, DX_NONE_GRAPH, FALSE);
	}
}

SceneBase::SceneBase() :
	m_fadeMask(-1),
	m_isInit(false),
	m_fadeFrame(kFadeFrameDefault),
	m_fadeTotalFrame(kFadeFrameDefault),
	m_fadeDir(0),
	m_fadeColor(0x000000),
	m_fadePlayerKind(0),
	m_isDispLoading(false),
	m_loadFrame(0),
	m_isDispCursor(true),
	m_isEnd(false),
	m_pNext(nullptr)
#ifdef DISP_PROCESS
	,m_updateTime(0),
	m_drawTime(0)
#endif
{
}

void SceneBase::setNextScene(SceneBase* pNext)
{
//	assert(!isFading());
	assert(!m_isEnd);

	m_isEnd = true;
	m_pNext = pNext;

	startFadeOut();
	// 遷移元と同じカラーでフェードするように設定する
	if (m_pNext)
	{
		m_pNext->setFadeColor(getFadeColor());
		m_pNext->setFadePlayerKind(getFadePlayerKind());
	}
}

float SceneBase::getFadeProgress() const
{
	return static_cast<float>(m_fadeFrame) / static_cast<float>(m_fadeTotalFrame);
}

void SceneBase::initAll()
{
	// フェードアウト状態から開始
	m_fadeFrame = m_fadeTotalFrame;
	startFadeIn();
	// 継承先シーンの初期化処理
	init();

	// マスク処理の準備
	CreateMaskScreen();

	m_fadeMask = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	SetMaskScreenGraph(m_fadeMask);
}

void SceneBase::endAll()
{
	// 継承先シーンの終了処理
	end();

	DeleteMask(m_fadeMask);	// TODO終了処理これであっているか怪しい
	DeleteGraph(m_fadeMask);

	DeleteMaskScreen();
}

void SceneBase::updateAll()
{
#ifdef DISP_PROCESS
	LONGLONG start = GetNowHiPerformanceCount();
#endif
	if (!isLoaded())
	{
		// リソースのロードにかかっているフレーム数をカウント
		m_loadFrame++;
	//	printfDx("LoadFrame : %d\n", m_loadFrame);
		return;	// ロード中は更新処理何も行わない
	}
	if (!m_isInit)
	{
		initAll();
		m_isInit = true;
	}

	updateFade();
	// 継承先シーンの更新処理
	update();
#ifdef DISP_PROCESS
	m_updateTime = GetNowHiPerformanceCount() - start;
#endif
}

void SceneBase::drawAll()
{
#ifdef DISP_PROCESS
	LONGLONG start = GetNowHiPerformanceCount();
#endif
	// 継承先シーンの描画処理
	draw();
//	drawCursor();
	drawFade();
	drawLoading();
	drawFront();
#ifdef _DEBUG
	drawDebug();
#endif

#ifdef DISP_PROCESS
	m_drawTime = GetNowHiPerformanceCount() - start;

	// 処理バーの表示
	// 説明 
	DrawString(0, Game::kScreenHeight - 48, "処理", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 48 + 2, 48 + 16 - 2, Game::kScreenHeight - 32 - 2, 0x0000ff, true);
	DrawString(0, Game::kScreenHeight - 32, "描画", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 32 + 2, 48 + 16 - 2, Game::kScreenHeight - 16 - 2, 0xff0000, true);

//	DrawBox(0,Game::kScreenHeight - 16, Game::kScreenWidth, Game::kScreenHeight,0xffffff, false);	// 外枠

	float rate = static_cast<float>(m_updateTime + m_drawTime) / 16666.6f;
	int width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0xff0000, true);	// 処理+描画
//	DrawFormatString(width, Game::kScreenHeight - 16, 0xffffff, "%d", m_updateTime + m_drawTime);

	rate = static_cast<float>(m_updateTime) / 16666.6f;
	width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0x0000ff, true);	// 処理+描画の上から処理時間のみ描画
#endif
}

bool SceneBase::isSceneEnd()
{
	// そもそも終わると言っていない
	if (!m_isEnd)	return false;
	// まだフェードアウト終わってない
	if (m_fadeFrame < m_fadeTotalFrame)	return false;
	
	return true;
}

void SceneBase::updateFade()
{
	// リソースのロードが完了していない
	if (m_fadeDir < 0 && (!isLoaded()))
	{
		return;	// ロード完了まではフェードイン処理を行わない
	}

	m_fadeFrame += m_fadeDir;
	if (m_fadeFrame >= m_fadeTotalFrame)
	{
		m_fadeFrame = m_fadeTotalFrame;
		m_fadeDir = 0;
	}
	if (m_fadeFrame <= 0)
	{
		m_fadeFrame = 0;
		m_fadeDir = 0;
	}
}

void SceneBase::drawFade() const
{
#if true
	// 完全に表示されている状態なのでフェードは表示しない
	if (m_fadeFrame <= 0)	return;

	// マスクの生成
	SetDrawScreen(m_fadeMask);
	ClearDrawScreen();

	constexpr int kHalfWidth = Game::kScreenWidth / 2;
	constexpr int kHalfHeight = Game::kScreenHeight / 2;

	float rate = getFadeProgress() / 0.9f;	// 0.9以上なら完全に隠れた状態にする
//	float rate = getFadeProgress();
	rate = min(rate, 1.0f);
	rate *= rate;

	// 真っ黒でプレイヤーを描画する
	SetDrawBright(0, 0, 0);
#if false
	double scale = 72.0 * (1.0f - rate);
	int animNo = (m_fadeFrame / 2) % Player::getRunAnimeNum();
	DrawRectRotaGraph(kHalfWidth, kHalfHeight, animNo * 32, 0, 32, 32, scale, 0.0, Player::getGraph(m_fadePlayerKind), true);
#else
	// 画面を分割してプレイヤーをたくさん表示
#if false
	constexpr int kSplitX = 16;
	constexpr int kSplitY = 9;
//	constexpr double kMaxScale = 72.0 / kSplitX;
	constexpr double kMaxScale = 6.0;
#else
	constexpr int kSplitX = 12;
	constexpr int kSplitY = 7;
	//	constexpr double kMaxScale = 72.0 / kSplitX;
	constexpr double kMaxScale = 8.0;
#endif
	constexpr int kSplitNum = kSplitX * kSplitY;
	constexpr int kIntervalX = Game::kScreenWidth / kSplitX;
	constexpr int kIntervalY = Game::kScreenHeight / kSplitY;
	constexpr int kStartX = kIntervalX / 2;
	constexpr int kStartY = kIntervalY / 2;

	for (int x = 0; x < kSplitX; x++)
	{
		

		for (int y = 0; y < kSplitY+1; y++)
		{
			// スケーリングにかかるフレーム数を変える
			int startFrame = (x+y) * 1;
			int endFrame = m_fadeTotalFrame - kSplitX + (x + y) * 1 - 1;
			if (m_fadeDir < 0)
			{
				startFrame = kSplitX - (x + y) * 1 - 1;
				endFrame = m_fadeTotalFrame - kSplitX + (kSplitX - (x + y) * 1 - 1) - 1;
			}

			const int kScaleFrameTotal = endFrame - startFrame;
			const int kCurrentFeame = m_fadeFrame - startFrame;

			double scaleRate = static_cast<double>(kCurrentFeame) / static_cast<double>(kScaleFrameTotal);
			scaleRate = max(0.0, scaleRate);

			if (scaleRate >= 1.0)	continue;

			double scale = kMaxScale * (1.0 - scaleRate);
			int animNo = (m_fadeFrame / 2) % Player::getRunAnimeNum();

			int posX = kStartX + kIntervalX * x;
			int posY = kStartY + kIntervalY * y - kIntervalY/2 * (x % 2);

			DrawRectRotaGraph(posX, posY, animNo * 32, 0, 32, 32, scale, 0.0, Player::getRunGraph(m_fadePlayerKind), true);
		}
	}
#endif

	// 元に戻す
	SetDrawBright(255, 255, 255);

	// フェード面の描画
	SetDrawScreen(DX_SCREEN_BACK);

	// マスク付きの矩形描画
	SetUseMaskScreenFlag(true);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
//	GradX_RGB(0, 0, Game::kScreenWidth, Game::kScreenHeight, (m_fadeColor >> 16) & 0xff, (m_fadeColor >> 8) & 0xff, (m_fadeColor >> 0) & 0xff, 255, 255, 255);

	// マスク設定戻す
	SetUseMaskScreenFlag(false);
#else
	// 完全に表示されている状態なのでフェードは表示しない
	if (m_fadeFrame <= 0)	return;

	float rate = getFadeProgress();
	int startX = 0;
	int endX = Game::kScreenWidth;

	if (m_fadeDir < 0)
	{
		// フェードイン中
		endX = static_cast<int>(Game::kScreenWidth * rate);
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int elem = GetRand(16) + 4;
			DrawLine(startX, y, endX - GetRand(128), y, GetColor(elem,elem,elem));
		}
	}
	else
	{
		// フェードアウト中
		startX = static_cast<int>(Game::kScreenWidth * (1.0f - rate));
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int elem = GetRand(16) + 4;
			DrawLine(startX - GetRand(128), y, endX, y, GetColor(elem, elem, elem));
		}
	}
#endif
}

void SceneBase::drawLoading() const
{
	if (m_isDispLoading && !isLoaded())
	{
#if false
		for (int i = 0; i < 8; i++)
		{
			int x = GetRand(Game::kScreenWidth);
			int y = GetRand(Game::kScreenHeight);

			DrawString(x,y,"ロード中",0xffffff);
		}
#endif
		float progress = getLoadProgress();
		if (progress >= 0.0f)
		{
			// ロード進捗のデバッグ表示
			constexpr int kBoxLeft = 120;
			constexpr int kBoxRight = Game::kScreenWidth - 120;
			constexpr int kBoxTop = Game::kScreenHeight - 160;
			constexpr int kBoxBottom = Game::kScreenHeight - 80;
			constexpr int kBoxLen = kBoxRight - kBoxLeft;
			DrawBox(kBoxLeft, kBoxTop, static_cast<int>(kBoxLeft + kBoxLen * progress), kBoxBottom, 0xffffff, true);
			DrawBox(kBoxLeft, kBoxTop, kBoxRight, kBoxBottom, 0xffffff, false);

			DrawFormatString(kBoxLeft + 8, kBoxBottom - 48, 0x000000, "ロード中…");
			DrawFormatString(kBoxLeft + 8, kBoxBottom - 32, 0x000000, "%3.1f %%", progress * 100);
		}
	}
}

void SceneBase::drawCursor() const
{
	if (!m_isDispCursor)	return;

	int count = 0;
	int size = kCursorSize / 2;
	for (int i = 0; i < Mouse::getLogNum(); i++)
	{
		float rate = static_cast<float>(i) / static_cast<float>(Mouse::getLogNum() - 1);
		if (rate < 0.0f)	rate = 0.0f;
		if (rate > 1.0f)	rate = 1.0f;
		rate = 1.0f - rate;
		int alpha = static_cast<int>(255 * rate);

		Vec2 pos = Mouse::getPos(i);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawLine(static_cast<int>(pos.x), static_cast<int>(pos.y) - size,
			static_cast<int>(pos.x), static_cast<int>(pos.y) + size,
			0xffffff, 3);
		DrawLine(static_cast<int>(pos.x) - size, static_cast<int>(pos.y),
			static_cast<int>(pos.x) + size, static_cast<int>(pos.y),
			0xffffff, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		size -= 1;
		count++;
	}
}

bool SceneBase::isFadingIn() const
{
	if (m_fadeDir < 0)	return true;
	return false;
}

bool SceneBase::isFadingOut() const
{
	if (m_fadeDir > 0)	return true;
	return false;
}

void SceneBase::startFadeIn()
{
	m_fadeDir = -1;
	// フェードイン処理は色、プレイヤーを決定しない(前のシーンのフェードアウト情報を使用する)
}

void SceneBase::startFadeOut()
{
//	Sound::getInstance().play("sceneChange");
	m_fadeDir = 1;
	m_fadePlayerKind = GetRand(Player::getKindNum() - 1);

	int colorNo = GetRand(kFadeColorNum - 1);
	m_fadeColor = kFadeColor[colorNo];
}
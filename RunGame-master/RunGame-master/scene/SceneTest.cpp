#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"
#include "SceneDebug.h"

#include "Pad.h"
#include "Mouse.h"

#include <string>
#include <cassert>

#include "Player.h"

#include "Font.h"
#include "DispRecord.h"

namespace
{
}

SceneTest::SceneTest():
	m_frameCount(0),
	m_maskHandle(-1)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示を行わない


	CreateMaskScreen();
}

void SceneTest::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

//	m_maskHandle = LoadMask("data/image/player01/Run.png");
	m_maskHandle = MakeScreen(640,480,true);

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneTest::isLoaded() const
{
//	if (!Player::isLoaded())	return false;
//	if (CheckHandleASyncLoad(handle))	return false;
	return true;
}

void SceneTest::init()
{
	m_pRecord = std::make_shared<DispRecord>();
	SetMaskScreenGraph(m_maskHandle);
}

void SceneTest::end()
{
	DeleteMask(m_maskHandle);

	DeleteMaskScreen();
}

void SceneTest::update()
{
	if (getFadeProgress() > 0.0f)
	{
		return;
	}
	m_frameCount++;

	m_pRecord->update();
	
#if false
	if ((Mouse::isTriggerLeft()) || m_frameCount > 120)
	{
		// 一度呼んだらもう一度呼ばないように！
		// 呼んだらフェードアウトが始まるのでこのソースではisFadingではじいている
		setNextScene(new SceneDebug);
	}
#endif
}

void SceneTest::draw()
{
	// リソースのロードが終わるまでは描画しないのがよさそう
	// (どちらにしろフェード仕切っているので何も見えないはず)
	if (!isLoaded())	return;

	// マスクの生成
	SetDrawScreen(m_maskHandle);

	ClearDrawScreen();

	static float sinRate = 0.0f;
	sinRate += 0.05f;
	int radius = 200 + static_cast<int>(200 * sinf(sinRate));
//	DrawCircle(640,480, radius,0x000000,true);

	// 真っ黒で描画
	SetDrawBright( 0, 0, 0);

//	DrawGraph(64, 64, Player::getGraph(0), true);
	double scale = 2.0f + sinf(sinRate);
	scale *= 4.0;
//	DrawRectRotaGraph(320, 240, 0, 0, 32, 32, scale, sinRate, Player::getGraph(0), true);
	DrawRectRotaGraph(320, 240, 0, 0, 32, 32, scale, 0.0, Player::getRunGraph(0), true);

	// 戻す
	SetDrawBright(255, 255, 255);

	// マスクの生成ここまで

	SetDrawScreen(DX_SCREEN_BACK);

	SetUseMaskScreenFlag(false);
	if(m_pRecord)	m_pRecord->draw();
	
//	DrawBox(0, 0, 320, 480, GetColor(255, 255, 0), TRUE);

	SetUseMaskScreenFlag(true);
	// maskテスト
//	DrawMask(64,240,m_maskHandle,DX_MASKTRANS_NONE);

	DrawBox(0, 0, 640, 480, GetColor(255, 0, 0), TRUE);

	DrawString(8,8,"SceneTest", 0xffffff);
	DrawFormatString(8, 8 + 16, 0xffffff, "FRAME:%d", m_frameCount);

	SetUseMaskScreenFlag(false);

	DrawRectRotaGraph(  64, 128, 0, 0, 32, 32, 1.0, 0.0, Player::getRunGraph(0), true);
	DrawRectRotaGraph( 128, 128, 0, 0, 32, 32, 2.0, 0.0, Player::getRunGraph(0), true);
	DrawRectRotaGraph( 256, 128, 0, 0, 32, 32, 4.0, 0.0, Player::getRunGraph(0), true);
	DrawRectRotaGraph( 512, 128, 0, 0, 32, 32, 8.0, 0.0, Player::getRunGraph(0), true);
	DrawRectRotaGraph(1024, 128, 0, 0, 32, 32, 24.0, 0.0, Player::getRunGraph(0), true);
}

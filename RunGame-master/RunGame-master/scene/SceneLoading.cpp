#include "SceneLoading.h"
#include "DxLib.h"

#include "Sound.h"
#include "Font.h"
#include "Bg.h"

#ifdef _DEBUG
#include "SceneDebug.h"
#else
#include "SceneTitle.h"
#endif

namespace
{
	// ロード終わっていても最低このフレーム数は待つ
	constexpr int kWaitFrameMin = 60;
}

SceneLoading::SceneLoading():
	m_frameCount(0)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示を行わない

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

SceneLoading::~SceneLoading()
{
}

void SceneLoading::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneLoading::isLoaded() const
{
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneLoading::init()
{
	// 背景演出
	m_pBg->setPlayerInterval(4);
	m_pBg->setPlayerCreateNum(1);
}

void SceneLoading::end()
{
	// フェードしきったあとに必要な情報の収集を行う

	// サウンドの情報収集
	Sound::getInstance().collectData();
	// フォントの情報収集
	Font::collectData();
}

void SceneLoading::update()
{
	m_pBg->update();

	if (getFadeProgress() > 0.0f)
	{
		return;
	}

	// ロード中のリソースがないか確認
	bool isLoading = false;
	if (!Sound::getInstance().isLoaded())
	{
	//	printfDx("sound loading...\n");
		isLoading = true;
	}
	if (!Font::isLoaded())
	{
	//	printfDx("font loading...\n");
		isLoading = true;
	}

	m_frameCount++;
//	printfDx("m_frameCount = %d\n", m_frameCount);
	if( (m_frameCount >= kWaitFrameMin) &&	// ロードが終わっても一定時間表示
		(!isLoading) )
	{
#ifdef _DEBUG
		setNextScene(new SceneDebug);
#else
		setNextScene(new SceneTitle);
#endif
	}
}

void SceneLoading::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();
	DrawString(64 + GetRand(4), 64 + GetRand(4), "Loading...", 0xffffff);
}

#ifdef _DEBUG
void SceneLoading::drawDebug()
{
	DrawString(8, 8, "SceneLoading", 0xffffff);
}
#endif

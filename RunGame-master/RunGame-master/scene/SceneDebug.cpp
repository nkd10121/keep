#include "DxLib.h"
#include "game.h"

#include "Player.h"
#include "Font.h"
#include "Sound.h"
#include "SceneDebug.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneMainMenu.h"
#include "SceneRecord.h"
#include "SceneConfig.h"
#include "SceneSelectPlayerNum.h"

#include "Pad.h"

#include "DebugUi.h"

#include <string>
#include <cassert>

namespace
{
}

SceneDebug::SceneDebug():
	m_frameCount(0)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示設定
//	setFadeFrame(8);		// フェードフレームを設定	設定せずにデフォルトフレームにしても良い
}

void SceneDebug::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);


	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneDebug::isLoaded() const
{
	return true;
}

void SceneDebug::init()
{
	m_pUi = std::make_shared<DebugUi>(8, 8);
	m_pUi->addItem(0, "タイトルから");
	m_pUi->addItem(1, "ゲームから");
	m_pUi->addItem(2, "メインメニュー");
	m_pUi->addItem(3, "人数選択");
	m_pUi->addItem(4, "ランキング");
	m_pUi->addItem(5, "コンフィグ");
	m_pUi->addItem(6, "test");
	m_pUi->addItem(7, "デモプレイ");
	m_pUi->setSelect(0);
}

void SceneDebug::end()
{
}

void SceneDebug::update()
{
	// フェードインアウト中はゲーム処理行わない
//	if (isFading())
	if(getFadeProgress() > 0.0f)
	{
		// フェード中も背景動かしたり待機アニメする場合はここで

		return;
	}

	// 通常はタイトル画面でロード待ちを行うが
	// デバッグメニューからは経由しない可能性があるのでここでロード待ち
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

	// ロード中のリーソースがある場合進めない
	if (isLoading)
	{
		return;
	}

	int result = m_pUi->update();

	m_frameCount++;

//	if(Pad::isTrigger(PAD_INPUT_1))
	if(result >= 0)	// 何かしら項目が選択された
	{
		// タイトル経由しないと初期周波数取得していないので収集しておく
		Sound::getInstance().collectData();
		// フォントの情報収集
		Font::collectData();

		switch (result)
		{
		case 0:	setNextScene(new SceneTitle);		break;
		case 1:	setNextScene(new SceneMain{ 1, false });	break;
		case 2:	setNextScene(new SceneMainMenu);	break;
		case 3:	setNextScene(new SceneSelectPlayerNum);	break;
		case 4:	setNextScene(new SceneRecord);		break;
		case 5:	setNextScene(new SceneConfig);		break;
		case 6:	setNextScene(new SceneTest);	break;
		case 7: setNextScene(new SceneMain{ Player::getKindNum(), true });	break;
		default:	setNextScene(new SceneTest);	break;
		}
	}
}

void SceneDebug::draw()
{
	if (!isInitialized())	return;
	// フェードインアウト中も描画は行う
//	if (isFading()) {}

	// リソースのロードが終わるまでは描画しないのがよさそう
	// (どちらにしろフェード仕切っているので何も見えないはず)
	if (!isLoaded())	return;

	m_pUi->draw();
}


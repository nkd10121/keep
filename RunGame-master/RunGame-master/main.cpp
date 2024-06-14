#include "DxLib.h"

#include "SaveData.h"
#include "ConfigData.h"
#include "Sound.h"
#include "Message.h"

#include <memory>
#include "game.h"
#include "SceneManager.h"
#include "Font.h"
#include "Player.h"

#include <filesystem>

#ifdef _DEBUG
//#define DISP_LOADTIME
#endif // _DEBUG

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef DISP_LOADTIME
	LONGLONG  loadStart = 0;
#endif

#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif


#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	// セーブデータ保存用のフォルダがない場合生成する
	if (!std::filesystem::is_directory("save"))
	{
		std::filesystem::create_directory("save");
	}

	// セーブデータ読み込み	フルスクリーン設定を読み込むので最初に
	SaveData::getInstance().load();
	ConfigData::getInstance().load();
#ifdef DISP_LOADTIME
	printfDx("savedata load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// windowモード設定
	ChangeWindowMode(!ConfigData::getInstance().isOn(ConfigData::FullScreen));
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// 画面が非アクティブでも動く
	SetAlwaysRunFlag(true);
	// ウインドウ、フルスクリーン切り替えに対応
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	// メッセージのロード
	Message::getInstance().load(static_cast<Message::LANG>(ConfigData::getInstance().getLanguage()));
#ifdef DISP_LOADTIME
	printfDx("messagedata load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// サウンドのロード
#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	Sound::getInstance().loadStart();
#ifdef DISP_LOADTIME
	printfDx("sound load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// フォントの読み込み、準備
#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif
	Font::loadStart();
#ifdef DISP_LOADTIME
	printfDx("font load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif
	// 常駐リソースの読み込み開始
	Player::startLoad();
#ifdef DISP_LOADTIME
	printfDx("player graph load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager;
	pScene->init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		if (!pScene->update())	break;

		pScene->draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->end();

	// 常駐リソースの解放
	Player::unload();

	// サウンドの解放
	Sound::getInstance().unload();

	// フォントの解放
	Font::unload();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
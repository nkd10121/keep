#include "DxLib.h"
#include "SceneMain.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//音楽のハンドル
	int handle =  LoadSoundMem("musicFile/MusMus-BGM-142.mp3");
	//音量調整
	ChangeVolumeSoundMem(255 * 60 / 100, handle);
	//音楽をバックグラウンドで再生(再生中も処理が動く)
	//PlaySoundMem(handle, DX_PLAYTYPE_BACK, true);

	SceneMain* sceneMain = new SceneMain;
	sceneMain->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		//このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		//ゲームの処理
		sceneMain->Update();
		sceneMain->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		//escキーでゲームを終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	//DeleteSoundMem(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
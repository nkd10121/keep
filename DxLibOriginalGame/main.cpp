#include "DxLib.h"

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

	int count = 0;

	int span = 9;

	int drawX = 320;
	int drawY = 240;

	int handle0 = LoadGraph("img/スライムA_攻撃000.png");
	int handle1 = LoadGraph("img/スライムA_攻撃001.png");
	int handle2 = LoadGraph("img/スライムA_攻撃002.png");
	int handle3 = LoadGraph("img/スライムA_攻撃003.png");
	int handle4 = LoadGraph("img/スライムA_攻撃004.png");

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		//このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		//ゲームの処理
		count++;
		if (count >= span * 6)
		{
			DrawGraph(drawX, drawY, handle0, true);
			count = 0;
		}
		else if (count >= span * 5)
		{
			DrawGraph(drawX, drawY, handle1, true);
		}
		else if (count >= span * 4)
		{
			DrawGraph(drawX, drawY, handle4, true);
		}
		else if (count >= span * 3)
		{
			DrawGraph(drawX, drawY, handle3, true);
		}
		else if (count >= span * 2)
		{
			DrawGraph(drawX, drawY, handle2, true);
		}
		else if (count >= span * 1)
		{
			DrawGraph(drawX, drawY, handle1, true);
		}
		else if (count >= span * 0)
		{
			DrawGraph(drawX, drawY, handle0, true);
		}

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

	DeleteGraph(handle0);
	DeleteGraph(handle1);
	DeleteGraph(handle2);
	DeleteGraph(handle3);
	DeleteGraph(handle4);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
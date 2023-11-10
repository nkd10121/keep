#include "DxLib.h"
#include <cmath>

namespace
{
	constexpr int width = 8;
	constexpr int height = 8;
}

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

	float x = 0;
	float y = 0;
	float rad = DX_PI / 180 * 10;


	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		x = x * cos(rad) - y * sin(rad) + 45;
		y = x * sin(rad) + y * cos(rad) - 55;


		DrawBox(x - width,
			y - height,
			x + width,
			y + height,
			0xffffff,
			true);

		DrawFormatString(0, 0, 0xffffff, "x = %f", x);
		DrawFormatString(0, 16, 0xffffff, "y = %f", y);

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
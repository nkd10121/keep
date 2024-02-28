#include "DxLib.h"
#include "DrawLib.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace Window
{
	constexpr int kWidth = 1280;
	constexpr int kHeight = 720;

	constexpr int kHalfWidth = static_cast<int>(kWidth * 0.5f);
	constexpr int kHalfHeight = static_cast<int>(kHeight * 0.5f);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);
	SetGraphMode(Window::kWidth, Window::kHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	std::string data;
	//std::string info;
	//std::string str_conma_buf;
	//std::string input_csv_file_path = "testData.csv";

	// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
	std::ifstream openFile("testData.csv");


	//// getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
	//while (getline(openFile, data)) {
	//	// 「,」区切りごとにデータを読み込むためにistringstream型にする
	//	std::istringstream i_stream(data);

	//	// 「,」区切りごとにデータを読み込む
	//	getline(i_stream, info, ',');
	//}

	getline(openFile, data);

	//printfDx("");

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		
		DrawFormatString(0, 0, 0xffffff, "%s", data);


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
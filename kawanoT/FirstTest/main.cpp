#include <DxLib.h>
#include <cassert>
#include <iostream>
#include "StringUtility.h"

using namespace std;

//int main()
//{
//	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
//
//	cout << a[7] << endl;
//	cout << 7[a] << endl;
//	cout << *(a + 7) << endl;
//
//	constexpr int row = 0;
//	constexpr int col = 0;
//
//	int b[row][col] == int c[row * col]
//
//}

//int MyLoadGraph(const wchar_t* path) {
//	int handle = LoadGraph(path);
//	assert(handle != -1);
//	return handle;
//}

/*ひとりでデバッグできるように*/
//①ブレークポイント(置いたところで止まる)
//	条件付きブレークポイント
//	→条件を満たしたときのみ止まる
//	1.値がおかしい場合だけ止めたい
//	2.巨大ループのn番目で止めたい
//	デメリット→めちゃめちゃ重くなる
//②実はブレーク中に変数の値を変更できます
//	1.変数にカーソルを合わせると値が見えるので
//		それをクリックすると値の変更が可能です
//	2.ブレーク中に「ローカル」というデバッグウィンドウを
//		見るとローカル変数がいくつか見えます。このローカルウィンドウから
//		変数を変更可能です。
// 
// ブレーク中にデバッグ→ウィンドウから表示しなおすことができる
//	ステップ実行(F10)ブレークした後F10で1行ずつ進む。
//	ただし、関数コールの部分では中に入らないためその時は
//	F11を使うと関数の中に入っていく
//	左の黄色い矢印はドラッグ＆ドロップで動かせる
// 
//	Debug/Release
// Debug:デバッグしやすい代わりに遅い(余計な情報が含まれている)
// Release:速い代わりにデバッグしずらい
// 
// 企業やコンテストに提出するときはReleaseで提出
// Debugは余計な情報が入っているためサイズが大きくなるうえに
// そもそもが遅いので相手のPCで思ったように動かない可能性がある
// 
// デバッグに役立つ話
//	1.ブレークポイントの使い方を覚える
//	・ブレークポイントで中断中は、ローカル座標を確認できる
//	・ついでに出力を見るとDxLibがログを出しているので失敗のログがないか確認する
//	2.中断したところからF10でi行ずつ確認する
//	 Releaseモードは有効ではない
// 　   2つの理由
//		①デバッグ情報がないため関数名、値がわからない
//		②プログラムが順番に実行されない
//	3.F11を使うと自作関数の中に入っていく
//	4.左の黄色い矢印はドラッグ＆ドロップで動かせる
//	5.ブレーク中に変数名にカーソルを合わせて数値を変更できる
//	6.ブレークポイントを右クリで条件を追加できる
//		条件を満たしたときのみ処理を中断する
//	7.データブレークポイント
//	->特定のメモリの内容が書き変わった時に中断
//	1度実行を始めてからでないとメモリの位置が確定しないため
//	実行中限定
// ->プログラムのどこで内容を書き換えているかわからない
//	特にメモリ破壊の時は、かってに値が変更されていることがある
//	そんな時に使える機能
//	8.呼び出し履歴
//	 ブレークしたところを呼び出した関数をさかのぼることができる
//	　また、呼び出した時点での周辺の変数も確認できる
//	9.ウォッチ機能
//	　指定した変数の値をアドレスを確認できる
//	
//


//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
	//ChangeWindowMode(true);	//非スクリーン
	//if (DxLib_Init() == -1) {	//初期化に失敗したらアプリを落とす
	//	return -1;	//異常終了
	//}

	//const char* bgPath = ("bg.png");
	//OutputDebugStringA("bg.png");

	//int bgH = MyLoadGraph(L"./bg.png");

	//実は表示される描画先には2枚のスクリーンがあります
	//これを高速でフリップ(入れ替え)を行うことで
	//画面のちらつきを無くしています
	//SetDrawScreen等の関数はDxLib_Init()の後じゃないと
	//有効ではないため注意
	//auto result = SetDrawScreen(DX_SCREEN_BACK);

	//int a = 0;

	//std::string titleStr = "川野";

	//while(ProcessMessage() != -1){
	//	ClearDrawScreen();

	//	auto wstr = StringUtility::StringToWString(titleStr);

	//	DrawString(50, 50, wstr.c_str(), 0xffffff);

	//	DrawFormatString(50, 50, 0xffffff, L"%s", wstr.c_str());

	//	ScreenFlip();

	//}
	//DxLib_End();

	//return 0;	//正常終了
//}


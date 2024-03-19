//#include <iostream>
//
//using namespace std;
//
//constexpr int kSize = 256;
//
////kSize*kSizeのマスがある
////x,y座標とサイズを指定して
////指定した座標からサイズ個のマスを塗りつぶす
//
////入力
//// x,y,size
//// x : 塗り始めるX座標 0始まり 0 <= x <= 9
//// y : 塗り始めるY座標 0始まり 0 <= x <= 9
//// size : 塗る範囲
//
////塗ったマスを"#",塗っていないマスを"."で表示せよ
//
////再帰を使う上での注意点
////処理が連鎖して大量に呼ばれる可能性がある
////一つ一つの処理は軽くても大量(100万回とかそんなレベル)で
////関数が呼ばれるのでスタックメモリが枯渇したり
//// 処理にとんでもない時間がかかったりする
//// 
//// PAIZAのAとかになってくると、処理時間との勝負になるので
//// 処理を減らす工夫が必要
//// 
//// 塗られている部分を塗りに行こうとする
//// 　→すでに塗られている部分は塗らない、とか
//// 　　sizeチェックして上きしないようにする　など必要
//// 
//// Paizaやるうえでは値の範囲が指定されているので
//// 値の範囲をチェックして処理時間を気にするかどうかを判断したりする
////
//
//
//void Draw(int dotData[kSize][kSize], int x, int y, int size)
//{
//	//塗らない
//	if (size <= 0)
//		return;
//
//	//範囲外は塗らない
//	if (x < 0)
//		return;
//	if (y < 0)
//		return;
//	if (x >= kSize)
//		return;
//	if (y >= kSize)
//		return;
//
//	dotData[x][y] = 1;
//
//	size--;
//
//	Draw(dotData, x - 1, y, size);	//左も塗る
//	Draw(dotData, x + 1, y, size);	//右も塗る
//	Draw(dotData, x, y - 1, size);	//上も塗る
//	Draw(dotData, x, y + 1, size);	//下も塗る
//}
//
//int main()
//{
//	//塗られる盤面のデータ
//	int dotData[kSize][kSize];
//	//盤面の初期化
//	for (int y = 0; y < kSize; y++)
//	{
//		for (int x = 0; x < kSize; x++)
//		{
//			dotData[x][y] = 0;
//		}
//	}
//
//	int startX, startY,size;
//	cin >> startX >> startY >> size;
//	//test
//	dotData[startX][startY] = 1;
//
//	Draw(dotData, startX, startY, size);
//
//
//	//最終的な盤面の表示
//	for (int y = 0; y < kSize; y++)
//	{
//		for (int x = 0; x < kSize; x++)
//		{
//			if (dotData[x][y] == 0)
//			{
//				cout << ".";
//			}
//			else
//			{
//				cout << "#";
//			}
//		}
//
//		//改行
//		cout << endl;
//	}
//}
//
//#if false	//再帰の基本
//void func(int count)
//{
//	cout << "再帰してみた" << count << endl;
//	count--;
//	if (count > 0)
//	{
//		func(count);
//	}
//
//}
//
//int main()
//{
//	// 再帰とは？
//	// 
//	// 再帰とはある関数から自身を呼び出す関数の処理のこと
//
//	// 何も考えずに再帰すると無限ループ
//	// いつかスタックメモリが使いつくされて止まる
//
//	// なので何かしらの条件で自身を呼び出すのをやめる
//	
//	int callCount;
//	cin >> callCount;
//
//	func(callCount);
//
//	return 0;
//}
//#endif
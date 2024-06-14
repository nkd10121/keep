#pragma once

// イベント特別版
#define EX_VER

namespace Game
{
	// ウインドウモード設定
//	constexpr bool kWindowMode = true;
	// ウインドウモード初期設定
	constexpr bool kDefaultWindowMode = true;
	// ウインドウ名
	const char* const kTitleText = "ホルゲーム！";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16


	// 最大プレイ人数
	constexpr int kMaxPlayer = 8;

#ifdef EX_VER
//	const char* const kExVerName = "Ver.エンクリ企業ミーティング";	// エンクリバージョン
	const char* const kExVerName = "オープンキャンパスに参加してくれてありがとう！";
#endif
};
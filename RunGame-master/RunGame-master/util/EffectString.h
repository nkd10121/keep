#pragma once
#include "Vec2.h"
#include <string>
#include <vector>
#include "Rect.h"

// 演出付き文字列表示クラス
class EffectString
{
public:
	// 表示エフェクトの種類
	enum class Effect
	{
		None,		// エフェクト無し通常描画
		Vibration,	// 1文字ずつ揺れる
		AlphaBlink,	// 点滅
	};

	// In演出の種類
	enum class In
	{
		None,		// なし　パッと表示
		Fade,		// フェードイン
	};

	// Out演出の種類
	enum class Out
	{
		None,		// なし　パッと消える
		Fade,		// フェードアウト
	};


public:
	EffectString();
	virtual ~EffectString();

	// 左上座標指定
	void setup(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setup(Vec2 pos, const char* str, int fontHandle, int kerning = 0);
	// 中心座標指定
	void setupCenter(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setupCenter(Vec2 pos, const char* str, int fontHandle, int kerning = 0);
	// 右上座標指定
	void setupRight(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setupRight(Vec2 pos, const char* str, int fontHandle, int kerning = 0);

	// ゲーム用設定
	// 各シーンのタイトル表示設定	画面中央上部に大きく表示
	void setupSceneTitle(const char* str);


	// 開始演出
	// wait:開始演出が始まるまでのフレーム数
	void startIn(In type, int wait = 0);
	// 終了演出
	// wait:終了演出が始まるまでのフレーム数
	void startOut(Out type, int wait = 0);

	// 開始演出終了しているかチェック(updateStaticの場合のみtrueを返す)
	bool isInEnd() const;

	// 表示設定
	void setColor(unsigned int color);

	// 表示エフェクトの種類を設定
	void setEffect(Effect effect);

	// 文字列クリア
	void clear();

	void update();
	void draw();

	// 文字の表示範囲を取得する
	Rect getRect() const;

private:

	// シーケンス別update
	void updateIn();
	void updateStatic();
	void updateOut();
	void updateOutEnd();

	// 演出別update処理
	void updateNone();
	void updateVibration();		// １文字ずつ揺れる
	void updateAlphaBlink();	// アルファ点滅

private:
	// 文字１文字分のデータ
	struct CharData
	{
		std::string chr;
		Vec2 basePos;	// 通常描画を行った場合の表示位置
		Vec2 dispPos;	// 実際に表示を行う位置
		unsigned int color;
		int alpha;

		float sinRate;	// 演出用
	};
private:
	// シーケンス別update処理
	void (EffectString::* m_updateFunc)() = &EffectString::updateIn;
	// 演出別update処理
	void (EffectString::* m_effectFunc)() = &EffectString::updateNone;
	// 使用するフォント
	int m_fontHandle;
	// １文字ずつに分解したデータ
	std::vector<CharData>	m_char;

	// カーニング(文字間隔)	デフォルト0でマイナスにすると詰まる
	int m_kerning;

	// 演出の種類
	Effect	m_effect;	// 表示演出
	In		m_in;		// In演出
	Out		m_out;		// Out演出

	// 表示制御
	int m_waitFrame;
	int m_frameCount;
};


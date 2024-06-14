#pragma once
#include "Vec2.h"
#include <memory>

class EffectPlayer;

// 数値を選択するUIを作成
// コンフィグ画面での音量選択などに使用する想定
class SelectValue
{
public:
	SelectValue();
	virtual ~SelectValue();

	void init(Vec2 center, int min, int max, int nowValue);
	void update();
	void draw();

	void setActive(bool isActive);
	int getValue() const { return m_value; }

private:

	float getValueRate();
	// バーの右端X座標取得
	int getBarEndX();
	// アイコン表示位置更新
	void updateValueIconPos();
	// 現在の音量、変化方向からアイコンの状態を更新する
	// 音量をあげたときは+1(>0),下げたときは-1(<0),デフォルトの時は0を指定
	void updateValueIconAnim(int change);

private:
	Vec2	m_center;
	bool m_isActive;

	int m_value;	// 現在の数値
	// 値の範囲
	int m_min;
	int m_max;

	std::shared_ptr<EffectPlayer>	m_pCurrectValue;
	std::shared_ptr<EffectPlayer>	m_pCursorL;
	std::shared_ptr<EffectPlayer>	m_pCursorR;
};


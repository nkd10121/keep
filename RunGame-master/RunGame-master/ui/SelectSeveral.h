#pragma once
#include "Vec2.h"
#include <vector>
#include <memory>

class EffectPlayer;

// 複数項目から1つを選択するUIを作成
// コンフィグ画面での言語選択などに使用する想定
class SelectSeveral
{
public:
	SelectSeveral();
	virtual ~SelectSeveral();

	void init(Vec2 center);
	void update();
	void draw();

	void addItem(const char* str, int value);
	// 初期設定(addItem,初期選択状態のsetSelect)を行った後に呼ぶ
	void setup();

	// 初期状態で選択されている項目を決定
	void setSelectIndex(int index);
	// valueから初期状態で選択されている項目を決定
	void setSelectValue(int value);

	void setActive(bool isActive);

	// 選択可能なアイテム数の取得
	int getItemNum();
	// 現在選択しているアイテムの番号を取得
	int getSelectNo();

	// 選択している項目に設定している数値を取得
	int getSelectValue();
	int getValue(int index);

private:
	struct Item
	{
		const char* str;
		int value;
	};

private:
	// 選択している項目の文字幅に合わせてカーソル表示位置を更新
	void updateCurorPos();

private:
	Vec2	m_center;
	int	m_selectNo;
	bool m_isActive;
	float m_cursorMoveX;

	std::vector<Item>	m_item;
	std::shared_ptr<EffectPlayer>	m_pCursorL;
	std::shared_ptr<EffectPlayer>	m_pCursorR;
};


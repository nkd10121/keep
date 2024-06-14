#pragma once
#include "Vec2.h"

class DebugUiItem
{
public:
	DebugUiItem(int index, Vec2 pos, const char* str);
	virtual ~DebugUiItem();

	void update();
	void draw();

	// 選択状態になった時に呼ばれる処理
	void OnSelect();
	// 選択状態でなくなった時に呼ばれる処理
	void OnUnselect();

	// データの取得
	int getIndex() const { return m_index; }
	Vec2 getPos() const { return m_pos; }

	// 現在選択されている項目か
	bool isSelecting() const { return m_isSelect; }

private:
	int m_index;	// 管理番号
	Vec2 m_pos;		// 表示位置
	const char* m_str;	// 表示する文字列

	bool m_isSelect;
};


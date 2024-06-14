#pragma once
#include <memory>
#include <vector>

class DebugUiItem;
class DebugUi
{
public:
	// デバッグメニューの左上座標を指定する
	DebugUi(int x = 0, int y = 0);
	virtual ~DebugUi();

	int update();	// 何か選択されたフレームにそのインデックスを返す	それ以外は-1
	void draw();

	// 項目の追加	indexは0から始まる通し番号を想定
	void addItem(int index, const char* str);

	// 強制的に指定した番号を選択状態にする
	void setSelect(int index);

	// 選択中の項目取得	何も選択されていない場合は-1
	int getSelectIndex();

private:
	std::vector<std::shared_ptr<DebugUiItem>>	m_pItem;

	// 上下での項目ループ
	bool m_isLoop;

	// メニューの左上位置
	int m_offsetX;
	int m_offsetY;

	// 上下リピート入力
	int m_repeatUp;
	int m_repeatDown;
};


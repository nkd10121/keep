#pragma once
#include "Vec2.h"
#include "Rect.h"

#include <memory>
#include <vector>

class PadUiItem;
class PadUi
{
public:
	PadUi();
	virtual ~PadUi();

	void setButtonGraph(int handle) { m_buttonGraph = handle; }

	int update();	// 何か選択されたフレームにそのインデックスを返す	それ以外は-1
	void draw();

	// 項目の追加	indexは0から始まる通し番号を想定
	void addItem(std::shared_ptr<PadUiItem> pItem);			// 個別に生成したものを追加
	void addItem(int index, const char* str, Rect rect);	// rect指定
	void addItem(int index, const char* str, Vec2 center, int width, int height);	// 中心座標(Vec2)、幅高さ指定
	void addItem(int index, const char* str, int centerX, int centerY, int width, int height);	// 中心座標(x,y)、幅高さ指定

	// 各ボタンの遷移先設定	簡単設定 縦に並んだUI、横に並んだUIを簡単に設定する
	// 上下左右に移動するようなUIの場合は個々のボタンに自分で設定する
	// addItemが終わってから行う
	// isLoop=trueの場合端から逆の端にループする
	void setupVArrange(bool isLoop);	// 縦に並んで配置されたボタンの遷移設定
	void setupHArrange(bool isLoop);	// 横に並んで配置されたボタンの遷移設定

	// UIの端でループを行うかの設定
	void setLoop(bool isLoop) { m_isLoop = isLoop; }

	// 強制的に指定した番号を選択状態にする
	void setSelect(int index);

	// 選択中の項目取得	何も選択されていない場合は-1
	int getSelectIndex();

	std::shared_ptr<PadUiItem> getItem(int index);

	//操作可能か
	bool isOperable() const;

	// 現在選択されている項目で決定できるか
	bool isDecideEnable();

private:
	std::vector<std::shared_ptr<PadUiItem>>	m_pItem;

	// ボタン表示に使用するグラフィック
	int m_buttonGraph;

	// 端での項目ループ
	bool m_isLoop;

	// リピート入力
	std::vector<int> m_repeatFrame;

	

	// 演出用
	float m_sinRate;
};


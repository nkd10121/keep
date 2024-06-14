#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class EffectString;
class PadUiItem
{
public:
	PadUiItem(int index, const char* str);
	virtual ~PadUiItem();

	// 表示内容生成に必要な情報を設定
	void setBorderHandle(int handle) { m_borderHandle = handle; }	// 枠線用のグラフィック
	void setRect(Rect rect) { m_rect = rect; }						// 表示範囲
	void setFont(int fontHandle) { m_font = fontHandle; }			// 使用フォント
	void setKarning(int karning) { m_karning = karning; }			// 文字間隔

	// 選択されている時、選択されていないときのスケール設定
	void setSelectScale(double scale);
	void setUnselectScale(double scale);

	// この項目で決定することができるか
	void setDecideEnable(bool isEnable) { m_isDecideEnable = isEnable; }
	bool isDecideEnable() const { return m_isDecideEnable; }

	// 設定された情報を元に表示内容を決定する
	void setup();

	// 上下左右キーを押したときに移動する先のインデックスを設定する
	// 移動しない場合は-1指定	(指定しなかった場合も-1)
	void setTriggerUp(int next) { m_trgUp = next; }
	void setRepeatUp(int next) { m_repUp = next; }
	void setTriggerDown(int next) { m_trgDown = next; }
	void setRepeatDown(int next) { m_repDown = next; }
	void setTriggerLeft(int next) { m_trgLeft = next; }
	void setRepeatLeft(int next) { m_repLeft = next; }
	void setTriggerRight(int next) { m_trgRight = next; }
	void setRepeatRight(int next) { m_repRight = next; }

	int getTriggerUp() const { return m_trgUp; }
	int getRepeatUp() const { return m_repUp; }
	int getTriggerDown() const { return m_trgDown; }
	int getRepeatDown() const { return m_repDown; }
	int getTriggerLeft() const { return m_trgLeft; }
	int getRepeatLeft() const { return m_repLeft; }
	int getTriggerRight() const { return m_trgRight; }
	int getRepeatRight() const { return m_repRight; }


	void update();
	void draw();

	///////////////////////////////////////////
	// 状態遷移
	///////////////////////////////////////////
	// 登場演出開始	開始までの時間設定も可能
	void start(int wait = 0);
//	// 登場演出を飛ばして待機状態に
//	void forceStart();
	// 決定した 
	void decide();
	// 選ばれなかったUIを消す演出開始
	void eraseNoDecide();

	// 選択状態になった時に呼ばれる処理
	void onSelect();
	// 選択状態でなくなった時に呼ばれる処理
	void onUnselect();

	// データの取得
	int getIndex() const { return m_index; }
	
	// 現在選択されている項目か
	bool isSelecting() const { return m_isSelect; }

	// 表示範囲の矩形取得
	Rect getRect() const { return m_rect; }

	// 操作してもいいか(登場演出中だったりしないか)
	bool isOperable() const;

	// 表示している演出付き文字データの取得
	std::shared_ptr<EffectString> getEffectString() const { return m_pString; }

private:
	// 土台部分の描画
	void drawBase();

	// 表示色の更新
	void updateDispColor();
	// 表示色の取得
	unsigned int getDispColor();

	// 状態ごとのupdate処理
	void updateWait();		// 登場前待機
	void updateAppear();	// 登場演出
	void updateIdle();		// 登場済み待機
	void updateDecide();	// 決定演出
		// 決定演出終了済み
	void updateErase();	// (他のボタンが選択されて)消える演出
		// 消える演出終了済み

private:
	// メンバー関数ポインタ
	void (PadUiItem::*m_updateFunc)() = &PadUiItem::updateWait;

	// 演出等を行うためにいったんグラフィックに描画してからそれを描画
	int m_graphHandle;

	// 枠線用のグラフィック
	int m_borderHandle;
	// 表示範囲の矩形
	Rect m_rect;
	// 文字のフォントハンドル
	int m_font;
	// カーニング
	int m_karning;

	// この項目で決定可能か
	bool m_isDecideEnable;

	// 表示色
	int m_colorR;
	int m_colorG;
	int m_colorB;

	int m_alpha;

	double m_selectScale;		// 選択されている時のスケール
	double m_unselectScale;		// 選択されていない時のスケール

	int m_index;		// 内部的な管理番号
	const char* m_str;	// ボタンに表示するメッセージ

	bool m_isSelect;	// 選択状態

	// 演出関連
	int m_frameCount;
	int m_startWait;	// 登場開始までのフレーム数	-1の場合は進まない
	double m_scale;

	// 文字列表示用のデータ
	std::shared_ptr<EffectString>	m_pString;

	// 各キーを押したときに移動する先のボタンインデックス
	// 移動しない場合は-1
	int m_trgUp;	// 上キーをトリガーしたときに移動するItemのインデックス
	int m_repUp;	// 上キーのリピートが入力されたときに移動するItemのインデックス
	int m_trgDown;
	int m_repDown;
	int m_trgLeft;
	int m_repLeft;
	int m_trgRight;
	int m_repRight;

};


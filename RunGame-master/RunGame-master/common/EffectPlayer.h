#pragma once
#include "Vec2.h"

// 演出用プレイヤー表示クラス
// 基本的にまっすぐ前に進むことを想定して実装
class EffectPlayer
{
public:
	EffectPlayer();
	virtual ~EffectPlayer();

	void setupIcon(Vec2 pos);	// 移動しないアイコンとしてセットアップ
								// 位置とベクトル(移動しない)位しか設定してない
	void setupTitle();		// タイトルの背景に表示する用セットアップ
	void setupPlayMob(float dt);	// プレイ中画面上部に出す演出用セットアップ	現在のゲーム進行速度を渡す(デフォルト1.0)

	void update();
	void draw();

	bool isExist() const { return m_isExist; }

	// 直接設定
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setScale(double scale) { m_scale = scale; }
	void setKind(int kind) { m_playerKind = kind; }
	void setAnimSpeed(int speed) { m_animSpeed = speed; }	// アニメ1コマのフレーム数を指定する(1以上)	小さいと早い
	void setRun(bool isRun) { m_isRun = isRun; }
	void setMove(bool isMove) { m_isMove = isMove; }	// falseだとsetVecで決めた方向を向くだけで移動しない	デフォルトtrue

	// プレイヤーの種類をランダムに変更する
	void setRandomKind();

	Vec2 getPos() const { return m_pos; }
	Vec2 getVec() const { return m_vec; }
	int getPlayerKind() { return m_playerKind; }

private:
	Vec2	m_pos;		// 中心座標
	Vec2	m_vec;
	double m_scale;

	int m_playerKind;
	int m_animFrame;
	int m_animSpeed;	// アニメ1コマのフレーム数	小さいと早い

	bool m_isMove;		// true:m_vecの方向に移動する	false:m_vecは回転角度を指定するのに使う
	bool m_isRun;		// false:待機アニメ
	bool m_isExist;
};


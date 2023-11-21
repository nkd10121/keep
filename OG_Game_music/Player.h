#pragma once
#include "Vec2.h"
#include "Rect.h"

class Input;

class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void Update(Input& input);
	void Draw();

	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	int SetKnockBackSpeed(int speed) { return m_knockBackSpeed = speed; }

	float GetPlayerPosX()const;

	//プレイヤーが敵に当たった時の処理
	void HitEnemy();

private:
	Vec2 m_pos;
	Vec2 m_colPos;

	int ScreenSizeW;
	int ScreenSizeH;

	//当たり判定用の矩形
	Rect m_colRect;

	//Padのスティックを傾けた向きと大きさを入れるよう
	int m_padStickX;
	int m_padStickY;

	//プレイヤーのスピード
	float m_speed;

	//ダッシュを押したときのカウント
	int m_dashCount;
	//ダッシュしているか
	bool m_isDash;
	//長押しかどうか判定するよう
	bool m_dashLog;

	//敵に当たった回数
	int hitCount;

	//ノックバックした時のスピード
	int m_knockBackSpeed;

	//敵にヒットした時プレイヤーが点滅するように
	int m_damageDrawFrame;

	//敵にヒットした時に無敵時間
	int m_playerInvincibleTime;
};


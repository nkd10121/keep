#pragma once
#include "../Vec2.h"
#include "../Rect.h"

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

	int SetKnockBackSpeed(int speed) { return knockBackSpeed = speed; }

private:
	Vec2 m_pos;
	Vec2 m_colPos;

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

	//ノックバックした時のスピード
	int knockBackSpeed;
};


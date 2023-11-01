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

private:
	Vec2 m_pos;
	Vec2 m_colPos;

	//当たり判定用の矩形
	Rect m_colRect;

	int m_padStickX;
	int m_padStickY;

	float m_speed;

	int m_count;

	bool m_isDash;
	bool m_dashLog;

};


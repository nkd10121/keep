#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void Update();
	void Draw();

	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	Vec2 m_pos;

	//当たり判定用の矩形
	Rect m_colRect;

	int posX;
	int posY;

	float speed;

	int count;

	bool dashFlag;
	bool dashLog;

};


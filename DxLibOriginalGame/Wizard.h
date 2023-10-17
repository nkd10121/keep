#pragma once
#include "Vec2.h"
//#include "Rect.h"

class Wizard
{
public:
	Wizard();
	~Wizard();

	void Init();
	void Update();
	void Draw();

private:
	//移動速度
	float m_speed;

	//フレーム数
	int m_frameNum;

	//乱数を入れるよう
	int m_randNum;

	//スライムのハンドル
	int m_handle;
	int m_handle0;
	int m_handle1;

	//歩きアニメーション
	int m_walkAnimFrame;

	//待機アニメーション
	int m_walkIdleFrame;

	//移動しているかどうか
	bool m_isMove;

	//アニメーションの切り替え用
	int m_srcX;
	int m_srcY;

	bool m_isRight;

	//表示位置
	Vec2 m_pos;
};

#pragma once
#include "Vec2.h"

class Slime
{
public:
	//向いている方向
	enum Dir
	{
		kDirLeft,	//左	= 0
		kDirRight,	//右	= 1
	};

public:
	Slime();
	~Slime();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

private:
	int m_handle;	//グラフィックのハンドル

	//表示位置
	Vec2 m_pos;

	//向いている方向
	Dir m_dir;

	//歩きアニメーション
	int m_walkAnimFrame;
};


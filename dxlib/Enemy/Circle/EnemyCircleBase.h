#pragma once
#include "../Enemy.h"
#include "DxLib.h"
#include "../../Util/Vec2.h"
#include "../../Util/Col.h"

class EnemyCircleBase : public Enemy
{
public:
	EnemyCircleBase();
	~EnemyCircleBase();

	//純粋仮想関数(継承先でオーバーロードする)
	//EnemyCircle用スタート関数
	virtual void Start(float pos, int radius, bool isSmooth) {};
	//EnemyBurstedCircle用スタート関数
	virtual void Start(Vec2 pos, Vec2 vec, int speed, int first, int second) {};
	//EnemyCircleScaling用スタート関数
	virtual void Start(Vec2 pos,int rad, int time = 60, int draw = 120,int speed = 20) {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// 当たり判定の座標を取得する
	/// </summary>
	/// <returns>当たり判定の座標</returns>
	Col GetColRect() const { return m_col; }

	/// <summary>
	/// 画面内に存在するかのフラグを返す
	/// </summary>
	/// <returns>存在しているかフラグ</returns>
	bool isExist() const { return m_isExist; }
protected:
	Vec2 m_pos;

	/// <summary>
	/// 始点座標
	/// </summary>
	Vec2 m_startPos;
	/// <summary>
	/// 終点座標
	/// </summary>
	Vec2 m_endPos;

	/// <summary>
	/// 当たり判定の座標
	/// </summary>
	Col m_col;

	int m_color;

	bool m_isExist;
};
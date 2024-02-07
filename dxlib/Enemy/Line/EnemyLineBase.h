#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Col.h"
/// <summary>
/// EnemyLine系の基底クラス
/// </summary>
/// 
class EnemyLineBase
{
public:
	EnemyLineBase();
	virtual ~EnemyLineBase();

	//純粋仮想関数(継承先でオーバーロードする)
	
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <param name="pos">表示座標</param>
	/// <param name="width">敵の幅(大きさ)</param>
	virtual void Start(Vec2 pos, int width, int firstFrame, int secondFrame) {};
	virtual void Start(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre) {};
	void Start() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// 当たり判定の座標を取得する
	/// </summary>
	/// <returns>当たり判定の座標</returns>
	Col GetColRect() const { return m_colRect; }

	int GetShakeFrame() { return m_shakeFrame; }

	/// <summary>
	/// 画面内に存在するかのフラグを返す
	/// </summary>
	/// <returns>存在しているかフラグ</returns>
	bool isExist() const { return m_isExist; }

protected:
	/// <summary>
	/// 右上の座標x,y
	/// </summary>
	Vec2 startPos;
	/// <summary>
	/// 左下の座標x,y
	/// </summary>
	Vec2 endPos;

	/////////////////////
	/// <summary>
	/// 当たり判定の右上の座標x,y
	/// </summary>
	Vec2 startColPos;
	/// <summary>
	/// 当たり判定の左下の座標x,y
	/// </summary>
	Vec2 endColPos;
	/////////////////////

	/// <summary>
	/// 当たり判定の座標
	/// </summary>
	Col m_colRect;

	int lineWidth;

	int m_frame;
	int m_firstFrame;
	int m_secondFrame;

	int m_color = 0xff00ff;

	int m_shakeFrame = 0;
	bool isShake = false;

	bool m_isExist;
};


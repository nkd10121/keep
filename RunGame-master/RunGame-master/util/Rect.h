#pragma once
#include "Vec2.h"
// 矩形クラス
class Rect
{
public:
	// 座標の種類
	// 中心座標を取得したり、左上座標を指定して矩形生成したりする
	enum class PosType
	{
		Center,		// 中心
		LT,			// 左上座標
		Underfoot	// 足元(xは中心、yはbottom)
	};

public:
	Rect();
	virtual ~Rect() {}

	// 矩形情報生成
	void setup(PosType type, Vec2 pos, float width, float height);	// 基準位置+サイズ指定
	void setup(float left, float top, float right, float bottom);	// 上下左右の座標指定

	// 座標取得
	Vec2 getPos(PosType type) const;
	Vec2 getCenter() const { return getPos(PosType::Center); }
	
	// 上下左右
	float getLeft() const	{ return m_left; }
	float getRight() const	{ return m_right; }
	float getTop() const	{ return m_top; }
	float getBottom() const { return m_bottom; }
	// 上下左右位置直接操作
	void setLeft(float left) { m_left = left; }
	void setRight(float right) { m_right = right; }
	void setTop(float top) { m_top = top; }
	void setBottom(float bottom) { m_bottom = bottom; }

	// 幅取得
	float getWidth() const;
	// 高さ取得
	float getHeight() const;

	// 描画
	void draw(unsigned int color, bool isFill) const;

	// 他の矩形とのあたり判定
	bool isCollision( Rect& rect ) const;
	// 点とのあたり判定(点が矩形に含まれているかの判定)
	bool isCollision(Vec2 pos) const;

private:
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
};
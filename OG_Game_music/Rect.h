#pragma once
#include "Vec2.h"
//矩形の座標を管理するクラス
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//描画
	void Draw(unsigned int color, bool isFill);

	//左上座標と幅高さを指定
	void SetLT(float left, float top, float width, float height);

	//中心座標と幅高さを指定
	void SetCenter(float x, float y, float width, float height);


	//ゲームによっては中心座標で指定したり足元の座標で指定する
	//set関数があったほうが便利かもしれない

	//必要な情報を取得する
	float GetWidth() const;		//幅
	float GetHeight() const;	//高さ
	Vec2 GetCenter() const;		//中心座標

	//矩形同士の当たり判定
	bool IsCollision(const Rect& rect);

private:
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;

};


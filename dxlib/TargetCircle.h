#pragma once
#include "Util/Col.h"

class TargetCircle
{
public:
	TargetCircle();
	~TargetCircle();

	void Init(int x,int y,int handleNum);
	void Update();
	void Draw();

	void Rotation();
	void Big();

	void Flag() { isChangeRotationSpeed = true; }

	/// <summary>
	/// “–‚½‚è”»’è‚ÌÀ•W‚ğæ“¾‚·‚é
	/// </summary>
	/// <returns>“–‚½‚è”»’è‚ÌÀ•W</returns>
	Col GetColRect() const { return m_col; }

private:
	int m_frame;
	int m_x;
	int m_y;
	float m_size;
	float tempSize = 0;
	float m_exRate;

	int handle;

	float angle = 0;

	bool isChangeRotationSpeed = false;

	Col m_col;
};
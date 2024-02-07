#pragma once
#include "../Util/Vec2.h"

class Efects
{
public:
	Efects(){};
	virtual ~Efects(){};

	bool isExist() { return m_isExist; }

	virtual void Init(Vec2 pos,bool isLastHit){};
	virtual void Update(){};
	virtual void Draw(){};

protected:
	bool m_isExist = false;

	int frame = 0;
	Vec2 m_pos;
	int rad = 20;
	int lineThick = 20;

	//dashEfect
	int alpha = 160;

	//goalEfect
	float angle = 0;


};


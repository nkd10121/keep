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

	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

private:
	Vec2 m_pos;

	//�����蔻��p�̋�`
	Rect m_colRect;

	int posX;
	int posY;

	float speed;

	int count;

	bool dashFlag;
	bool dashLog;

};


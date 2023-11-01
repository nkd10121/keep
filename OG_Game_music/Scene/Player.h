#pragma once
#include "../Vec2.h"
#include "../Rect.h"

class Input;

class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void Update(Input& input);
	void Draw();

	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

private:
	Vec2 m_pos;
	Vec2 m_colPos;

	//�����蔻��p�̋�`
	Rect m_colRect;

	int m_padStickX;
	int m_padStickY;

	float m_speed;

	int m_count;

	bool m_isDash;
	bool m_dashLog;

};

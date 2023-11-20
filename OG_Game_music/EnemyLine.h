#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyLine
{
public:
	EnemyLine();
	~EnemyLine();

	void Start();
	void Update();
	void Draw();

	//�����蔻����擾����
	Rect GetColRect() const { return colRect; }

	//���݂��Ă��邩
	bool isExist() const { return m_isExist; }

private:
	Vec2 startPos;
	Vec2 endPos;

	Vec2 startColPos;
	Vec2 endColPos;
	
	Rect colRect;

	int frame;

	bool m_isExist;
};


#pragma once
#include "EnemyLineBase.h"

/// <summary>
/// �ォ��o�Ă��郉�C���n�̓G
/// </summary>
class EnemyLineFromUpper	: public EnemyLineBase
{
public:
	EnemyLineFromUpper();
	~EnemyLineFromUpper();

	virtual void Start(Vec2 pos, int width, int firstFrame, int secondFrame) override;
	virtual void Update()override;
	virtual void Draw()override;
};


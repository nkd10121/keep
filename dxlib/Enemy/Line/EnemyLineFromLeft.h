#pragma once
#include "EnemyLineBase.h"

/// <summary>
/// ������o�Ă��郉�C���n�̓G
/// </summary>
class EnemyLineFromLeft : public EnemyLineBase
{
public:
	EnemyLineFromLeft();
	~EnemyLineFromLeft();

	virtual void Start(Vec2 pos, int width, int firstFrame, int secondFrame) override;
	virtual void Update()override;
	virtual void Draw()override;
};


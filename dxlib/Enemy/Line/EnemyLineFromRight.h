#pragma once
#include "EnemyLineBase.h"

/// <summary>
/// �E����o�Ă��郉�C���n�̓G
/// </summary>
class EnemyLineFromRight :	public EnemyLineBase
{
public:
	EnemyLineFromRight();
	~EnemyLineFromRight();

	virtual void Start(Vec2 pos, int width, int firstFrame, int secondFrame) override;
	virtual void Update()override;
	virtual void Draw()override;
};
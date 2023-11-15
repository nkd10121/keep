#pragma once
class EnemyLine
{
public:
	EnemyLine();
	~EnemyLine();

	void Draw();
	void Update();

private:
	int startPosX;
	int startPosY;

	int endPosX;
	int endPosY;
};


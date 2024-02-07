#pragma once

class GraphManager;

class DrawBGparts
{
public:
	DrawBGparts();
	~DrawBGparts();

	void Init(bool isMove);
	void Update();
	void Draw();

private:
	GraphManager gManager;

	int frame = 0;
	int handle = 0;
	bool m_isMove = false;

	//x���W
	int x = 0;
	//y���W
	int y = 0;
	//�䗦
	float exrate = 0.0f;
	//�p�x
	float angle = 0.0f;

	float rotateAngle = 0.0f;

	float rotateFrame = 0.0f;
	//���S����̔��a
	int rad = 0;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	float rotateSpeed = 0;
	float mag = 1.0f;
};


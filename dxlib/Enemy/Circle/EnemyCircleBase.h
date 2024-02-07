#pragma once
#include "../Enemy.h"
#include "DxLib.h"
#include "../../Util/Vec2.h"
#include "../../Util/Col.h"

class EnemyCircleBase : public Enemy
{
public:
	EnemyCircleBase();
	~EnemyCircleBase();

	//�������z�֐�(�p����ŃI�[�o�[���[�h����)
	//EnemyCircle�p�X�^�[�g�֐�
	virtual void Start(float pos, int radius, bool isSmooth) {};
	//EnemyBurstedCircle�p�X�^�[�g�֐�
	virtual void Start(Vec2 pos, Vec2 vec, int speed, int first, int second) {};
	//EnemyCircleScaling�p�X�^�[�g�֐�
	virtual void Start(Vec2 pos,int rad, int time = 60, int draw = 120,int speed = 20) {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// �����蔻��̍��W���擾����
	/// </summary>
	/// <returns>�����蔻��̍��W</returns>
	Col GetColRect() const { return m_col; }

	/// <summary>
	/// ��ʓ��ɑ��݂��邩�̃t���O��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă��邩�t���O</returns>
	bool isExist() const { return m_isExist; }
protected:
	Vec2 m_pos;

	/// <summary>
	/// �n�_���W
	/// </summary>
	Vec2 m_startPos;
	/// <summary>
	/// �I�_���W
	/// </summary>
	Vec2 m_endPos;

	/// <summary>
	/// �����蔻��̍��W
	/// </summary>
	Col m_col;

	int m_color;

	bool m_isExist;
};
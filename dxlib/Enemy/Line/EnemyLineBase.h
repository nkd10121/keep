#pragma once

#include "../../Util/Vec2.h"
#include "../../Util/Col.h"
/// <summary>
/// EnemyLine�n�̊��N���X
/// </summary>
/// 
class EnemyLineBase
{
public:
	EnemyLineBase();
	virtual ~EnemyLineBase();

	//�������z�֐�(�p����ŃI�[�o�[���[�h����)
	
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <param name="pos">�\�����W</param>
	/// <param name="width">�G�̕�(�傫��)</param>
	virtual void Start(Vec2 pos, int width, int firstFrame, int secondFrame) {};
	virtual void Start(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre) {};
	void Start() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// �����蔻��̍��W���擾����
	/// </summary>
	/// <returns>�����蔻��̍��W</returns>
	Col GetColRect() const { return m_colRect; }

	int GetShakeFrame() { return m_shakeFrame; }

	/// <summary>
	/// ��ʓ��ɑ��݂��邩�̃t���O��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă��邩�t���O</returns>
	bool isExist() const { return m_isExist; }

protected:
	/// <summary>
	/// �E��̍��Wx,y
	/// </summary>
	Vec2 startPos;
	/// <summary>
	/// �����̍��Wx,y
	/// </summary>
	Vec2 endPos;

	/////////////////////
	/// <summary>
	/// �����蔻��̉E��̍��Wx,y
	/// </summary>
	Vec2 startColPos;
	/// <summary>
	/// �����蔻��̍����̍��Wx,y
	/// </summary>
	Vec2 endColPos;
	/////////////////////

	/// <summary>
	/// �����蔻��̍��W
	/// </summary>
	Col m_colRect;

	int lineWidth;

	int m_frame;
	int m_firstFrame;
	int m_secondFrame;

	int m_color = 0xff00ff;

	int m_shakeFrame = 0;
	bool isShake = false;

	bool m_isExist;
};


#pragma once

//�����蔻����Ǘ�����N���X
class Col
{
public:
	Col();
	virtual ~Col();

	/// <summary>
	/// �l�p�̓����蔻��͈̔͂�`��
	/// </summary>
	/// <param name="color">�F</param>
	void DrawColBox(unsigned int color);

	/// <summary>
	/// �~�̓����蔻��͈̔͂�`��
	/// </summary>
	/// <param name="color">�F</param>
	void DrawColCircle(unsigned int color);

	/// <summary>
	/// �l�p�̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="left">����x���W</param>
	/// <param name="top">���y���W</param>
	/// <param name="right">�E��x���W</param>
	/// <param name="bottom">����y���W</param>
	void SetBox(float left, float top, float right, float bottom);

	/// <summary>
	/// �l�p�̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="left">����x���W</param>
	/// <param name="top">���y���W</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	void SetLT(float left, float top, float width, float height);

	/// <summary>
	/// �l�p�̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="x">���S��x���W</param>
	/// <param name="y">���S��y���W</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	void SetCenter(float x, float y, float width, float height);

	/// <summary>
	/// �~�̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="center"></param>
	/// <param name="m_rad"></param>
	void SetCircle(float x,float y, int m_rad);

	//�Q�[���ɂ���Ă͒��S���W�Ŏw�肵���葫���̍��W�Ŏw�肷��
	//set�֐����������ق����֗���������Ȃ�

	//�K�v�ȏ����擾����
	float GetWidth() const;		//��
	float GetHeight() const;	//����

	/// <summary>
	/// ��`���m�̓����蔻��
	/// </summary>
	/// <param name="col">: ��`�̓����蔻��</param>
	/// <returns></returns>
	bool IsCollision(const Col& col);
	
	/// <summary>
	/// ��`�Ɖ~�̓����蔻��
	/// ����:��`������Ăяo���K�v����
	/// </summary>
	/// <param name="col">: �~�̓����蔻��</param>
	/// <returns></returns>
	bool IsCollisionCircle(const Col& col);

private:
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;

	float m_centerX;
	float m_centerY;
	int m_rad;
};


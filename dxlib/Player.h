#pragma once
#include "Util/Vec2.h"
#include "Util/Col.h"
#include <vector>

class Input;
class AfterImagePlayer;
class Efects;

class Player
{
public:
	Player();
	~Player();
	
	void Init(bool isInStage);
	void Update(Input& input);
	void Draw();

	/// <summary>
	/// �v���C���[�̓����蔻����擾����
	/// </summary>
	/// <returns>�v���C���[�̓����蔻��̍��W</returns>
	Col GetColRect() const { return m_colRect; }


	/// <summary>
	/// �v���C���[�̉E����X���W���擾����
	/// </summary>
	/// <returns>�v���C���[�̉E����X���W</returns>
	Vec2 GetPlayerPos()const {return m_pos;}

	/// <summary>
	/// �v���C���[���G�ɓ����������̏���
	/// </summary>
	void HitEnemy();

	/// <summary>
	/// �G�ɓ��������񐔂�Ԃ�
	/// </summary>
	/// <returns>�G�ɓ���������</returns>
	int ReturnHitEnemyNum()const { return m_hitCount; }

	void CreateAfterImage(Vec2 pos,Vec2 vec, int size, bool isDash);

	void CreateDashEfect(Vec2 pos, bool isLastHit = false);

	void CreateHitEfect(Vec2 pos, bool isLastHit = false);
private:
	//�v���C���[�̃O���t�B�b�N�n���h��
	int playerHandle[4];

	bool m_isInStage;

	//�v���C���[�̈ʒu
	Vec2 m_pos;
	//�v���C���[�̓����蔻��̈ʒu
	Vec2 m_colPos;

	//��ʃT�C�Y Game::�ɒ���
	int ScreenSizeW;
	int ScreenSizeH;

	int frame = 0;

	//�����蔻��p�̋�`
	Col m_colRect;

	//Pad�̃X�e�B�b�N���X���������Ƒ傫��������悤
	int m_padStickX;
	int m_padStickY;

	//�X�e�B�b�N���͂̂���������float�ɂ���p
	float powerX;
	float powerY;

	float angle;

	//�v���C���[�̃X�s�[�h
	float m_speed;

	//�_�b�V�����������Ƃ��̃J�E���g
	int m_dashCount;
	//�_�b�V�����Ă��邩
	bool m_isDash;

	//�G�ɓ���������
	int m_hitCount;

	//�m�b�N�o�b�N�������̃X�s�[�h
	int m_knockBackSpeed;
	//Vec2 m_knockBackSpeed;

	//�G�Ƀq�b�g�������v���C���[���_�ł���悤��
	int m_damageDrawFrame;

	//�G�Ƀq�b�g�������ɖ��G����
	int m_playerInvincibleTime;

	std::vector<AfterImagePlayer*> afterImage;
	Vec2 m_posLog;

	std::vector<Efects*> efects;
};


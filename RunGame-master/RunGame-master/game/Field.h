#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>
#include <deque>
class PlayerManager;
class Field
{
public:
	Field(bool isDemo);
	virtual ~Field();

	void init();
	void update();
	void draw();

	void setHandle(int handle) { m_handle = handle; }
	// init���O�ɌĂяo���I
	void setPlayerManager(std::shared_ptr<PlayerManager> pPlayer) { m_pPlayer = pPlayer; }

	// �v���C���[�̓������`��񂩂�ړ��\�ȋ�`�����擾����
	Rect getMoveEnableRect(const Rect rect);

	// �@���������̈ʒu����ǉ�
	void addDigData(Vec2 pos, unsigned int color, int playerNo);
	// �����ʒu�p�̌��f�[�^�ǉ�
	void addStartDigData(Vec2 pos, unsigned int color, int playerNo);

	// �v���C���[�Ƃ̓����蔻��
	bool isCol(Vec2 pos);

private:
	// �n�ʂ̃f�[�^
	struct FieldChip
	{
		int y;
	};
	// �n�ʃf�[�^�c1��
	struct FieldLine
	{
		int x;
		std::vector<FieldChip>	chip;
	};

	// �@���������̃f�[�^
	struct DigData
	{
		Vec2 pos;
		int radius;
		unsigned int color;
	};

	// �n�`�f�[�^�����֘A�֐�

	// �����n�`�f�[�^����
	void initFieldLine();
	// ��ʃf�[�^�X�V	��ʊO�ɏo���������폜���ĐV���ɓ����Ă��镔���𐶐�����
	void updateFieldLine();

	// �c�P���C�����̃f�[�^����
	FieldLine createLine(int posX);

	// 1�u���b�N���̒n�`�f�[�^�������Ēǉ�
	void addFieldBlock(int startX);

	int addUpperWall(int startX, int lineNum);	// �㔼�����炢�𕢂���
	int addUnderWall(int startX, int lineNum);	// ���������炢�𕢂���

	int addPipe(int startX, int lineNum);		// �㉺�̕ǒǉ�
	int addHole(int startX, int lineNum);		// �����_���Ɍ����󂢂���

	// 
	void drawBg();

	// ��苗�����Ƃ̌��݋����\��
	void drawDistance();

	// �f���v���C	�㉺�ȊO��Q���o�Ȃ�
	bool isDemoPlay();

private:
	int m_handle;
	// �`�b�v�p�O���t�B�b�N���
	int m_graphW;
	int m_graphH;
	int m_chipNumX;
	int m_chipNumY;

	std::shared_ptr<PlayerManager> m_pPlayer;

	// �n�ʃf�[�^
	std::deque<FieldLine>	m_fieldData;

	// �@���������f�[�^
	std::vector<std::deque<DigData>>	m_digData;

	// �����[�g�������Ƀ��C��������
	int	m_lineNo;
	float m_lineSin;

	// �f���v���C	��Q���o�Ȃ�
	bool m_isDemo;
};


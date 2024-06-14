#pragma once
#include "Vec2.h"
#include <memory>
#include <vector>

// �����L���O���	��l���̃f�[�^�\��
class EffectPlayer;
class SingleRecord
{
public:
	struct DispData
	{
		// �f�[�^�\���ʒu
		int y;
		int rankX;
		int scoreX;
		// �A�C�R�����
		int iconX;
		double iconScale;
		int iconAnimSpeed;
		bool isIconRun;
	};

public:
	SingleRecord();
	virtual ~SingleRecord();

	// �v���C���[�ԍ���\�� -1���w��Ŕ�\��
	void setPlayerNo(int no) { m_playerNo = no; }
	// �ΐ탂�[�h�̏��ʕ\���ݒ�
	// �X�R�A���t���[�����Ƃ��Ă�������Ԃɕϊ����ĕ\������	�f�t�H���g��false
//	void setMulti(bool isMulti) { m_isMulti = isMulti; }
	// �ΐ탂�[�h�̏��ʕ\���ݒ�
	// �v���C���[�̐l�����w��	��l�v���C�Ń����L���O��\���������ꍇ��-1(�f�t�H���g)
	void setMultiPlayerNum(int num) { m_multiPlayerNum = num; }
	void setHightlight(bool isHighlight) { m_isHighlight = isHighlight; }

	// rank��0~9�œn��
	void setup(int index, int rank, int score, int playerKind, int fontHandle);

	void update();
	void draw();
	// �\���J�n�܂ł̃t���[�������w��
	void setDispWait(int wait) { m_dispWait = wait; }

	// ���S�ɕ\������Ă��邩���擾����
	bool isDisp();
	// �����I�Ɋ��S�ɕ\�����ꂽ��Ԃɂ���
	void forceDisp();
	// �ΐ탂�[�h�̌��ʕ\�����ǂ���
	bool isMulti();

private:
	// �A�C�R���̈ʒu���
	Vec2 getIconPos();

	// ?��	�̕\��	�E�[��X���W, ��[��Y���W���w�肷��
	void drawRank(int x, int y);
	// ????���[�g��	�̕\��"���[�g��"�̍��[X���W���w�肷��
	void drawScore(int x, int y);
	// �ΐ탂�[�h�p�X�R�A�\��	�t���[���������Ԃɕϊ����ĕ\��
	void drawScoreMulti(int x, int y);
	// �ΐ탂�[�h�p	�v���C���[�ԍ��\��
	void drawPlayerNo();

	// �A�C�R�������\�����o	�v���C���[�A�C�R���̌������ɕ\������
	void drawIconHighlight();

private:
	// �\������̂ɕK�v�ȃf�[�^
	int m_index;	// �\���ʒu
	int m_rank;		// �\�����鏇��	+1�����ʂƂ��ĕ\�������(0�Ȃ�1�ʂƕ\��)
	int m_score;
	int m_playerKind;
	int m_fontHandle;
	int m_playerNo;	// �ΐ탂�[�h���ɕ\������v���C���[�ԍ�	-1�̏ꍇ�͕\�����Ȃ�

	DispData m_dispData;	// �g�p����\���ʒu�f�[�^

//	bool m_isMulti;	// score�����ԂƂ��ĕ\������(�ΐ�v���C�p)	�f�t�H���g��false
	int m_multiPlayerNum;	// �ΐ탂�[�h�ł̃v���C�l��	1�l�v���C�Ń����L���O��\������ꍇ��-1
	bool m_isHighlight;	// �����\��������

	// �v���C���[�A�C�R��
	std::shared_ptr<EffectPlayer>	m_pIcon;

	// �\���ɕK�v�ȏ��
	std::vector<int>	m_numWidth;
	int		m_maxWidth;	// ��ԉ����̍L���t�H���g�̕�

	// �\���܂ł̑҂�����
	int m_dispWait;
	// �\���J�n����A���t�@�Ŋ��S�ɕ\������܂ł̃t���[����
	int m_dispAlphaFrame;
	// �\���J�n���̌��ʉ���炵��
	bool m_isPlaySe;

	// ���o�֘A
	float m_sinRate;
};


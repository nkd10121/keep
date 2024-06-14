#pragma once

#include <memory>
#include <vector>

// �����L���O�\��
class EffectString;
class EffectPlayer;
class SingleRecord;
class DispRecord
{
public:
	// �\������^�C�g��
	enum TitleType
	{
		None,
		Gameover,
		Ranking,
		MultiResult,

		Num
	};

public:
	DispRecord();
	virtual ~DispRecord();

	// �\������^�C�g���̐ݒ�	�\�����Ȃ��ꍇ��None������K�v�Ȃ�(setupTitle���Ă΂Ȃ���OK)
	void setupTitle(TitleType type);
	// �w�i�t�F�[�h�A���t�@�ݒ�	�f�t�H���g��0(�w�i�t�F�[�h����)
	void setBgAlpha(int alpha) { m_bgAlpha = alpha; }
	
	// �\������f�[�^�̓o�^
	// rank��0����̒ʂ��ԍ�	0���w�肵����1�ʂƂ��ĕ\�������
	// playerNo�͑ΐ�Ńv���C���[�ԍ���\���������Ƃ��w�肷��	0���w�肵����1P�Ƃ��ĕ\�������
	// �f�t�H���g��-1���Ɣ�\��
	// ��l�v���C�̏ꍇ��totalPlayerNum��-1���w��	�ΐ�̏ꍇ�͐l�����w�肷��
	void addData(int index, int rank, int score, int playerKind, int playerNo = -1, int totalPlayerNum = -1);

	// �\������܂ł̑҂����Ԃ�ݒ肷��
	void setDispWait(int index, int frame);

	void update();
	void draw();

	// �����\�����s���������ʂ��w�肷��	0~�̔ԍ��Ŏw��
	void setHighlightRank(int rank);

	// ���S�ɕ\�����I��������ǂ������擾
	bool isDispEnd();
	// �����I�Ɋ��S�ɕ\�����o���I��点�ĕ\����Ԃ�
	void forceDisp();

private:
	// 
	int m_frameCount;

	// �^�C�g��������
	std::shared_ptr<EffectString>	m_pTitle;
	// �e���ʂ̕\���f�[�^
	std::vector<std::shared_ptr<SingleRecord>>	m_pRecord;

	// �w�i�t�F�[�h�A���t�@	0�Ȃ�t�F�[�h�����A255�Ȃ�^����
	int		m_bgAlpha;
};


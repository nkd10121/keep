#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class EffectString;
class PadUiItem
{
public:
	PadUiItem(int index, const char* str);
	virtual ~PadUiItem();

	// �\�����e�����ɕK�v�ȏ���ݒ�
	void setBorderHandle(int handle) { m_borderHandle = handle; }	// �g���p�̃O���t�B�b�N
	void setRect(Rect rect) { m_rect = rect; }						// �\���͈�
	void setFont(int fontHandle) { m_font = fontHandle; }			// �g�p�t�H���g
	void setKarning(int karning) { m_karning = karning; }			// �����Ԋu

	// �I������Ă��鎞�A�I������Ă��Ȃ��Ƃ��̃X�P�[���ݒ�
	void setSelectScale(double scale);
	void setUnselectScale(double scale);

	// ���̍��ڂŌ��肷�邱�Ƃ��ł��邩
	void setDecideEnable(bool isEnable) { m_isDecideEnable = isEnable; }
	bool isDecideEnable() const { return m_isDecideEnable; }

	// �ݒ肳�ꂽ�������ɕ\�����e�����肷��
	void setup();

	// �㉺���E�L�[���������Ƃ��Ɉړ������̃C���f�b�N�X��ݒ肷��
	// �ړ����Ȃ��ꍇ��-1�w��	(�w�肵�Ȃ������ꍇ��-1)
	void setTriggerUp(int next) { m_trgUp = next; }
	void setRepeatUp(int next) { m_repUp = next; }
	void setTriggerDown(int next) { m_trgDown = next; }
	void setRepeatDown(int next) { m_repDown = next; }
	void setTriggerLeft(int next) { m_trgLeft = next; }
	void setRepeatLeft(int next) { m_repLeft = next; }
	void setTriggerRight(int next) { m_trgRight = next; }
	void setRepeatRight(int next) { m_repRight = next; }

	int getTriggerUp() const { return m_trgUp; }
	int getRepeatUp() const { return m_repUp; }
	int getTriggerDown() const { return m_trgDown; }
	int getRepeatDown() const { return m_repDown; }
	int getTriggerLeft() const { return m_trgLeft; }
	int getRepeatLeft() const { return m_repLeft; }
	int getTriggerRight() const { return m_trgRight; }
	int getRepeatRight() const { return m_repRight; }


	void update();
	void draw();

	///////////////////////////////////////////
	// ��ԑJ��
	///////////////////////////////////////////
	// �o�ꉉ�o�J�n	�J�n�܂ł̎��Ԑݒ���\
	void start(int wait = 0);
//	// �o�ꉉ�o���΂��đҋ@��Ԃ�
//	void forceStart();
	// ���肵�� 
	void decide();
	// �I�΂�Ȃ�����UI���������o�J�n
	void eraseNoDecide();

	// �I����ԂɂȂ������ɌĂ΂�鏈��
	void onSelect();
	// �I����ԂłȂ��Ȃ������ɌĂ΂�鏈��
	void onUnselect();

	// �f�[�^�̎擾
	int getIndex() const { return m_index; }
	
	// ���ݑI������Ă��鍀�ڂ�
	bool isSelecting() const { return m_isSelect; }

	// �\���͈͂̋�`�擾
	Rect getRect() const { return m_rect; }

	// ���삵�Ă�������(�o�ꉉ�o���������肵�Ȃ���)
	bool isOperable() const;

	// �\�����Ă��鉉�o�t�������f�[�^�̎擾
	std::shared_ptr<EffectString> getEffectString() const { return m_pString; }

private:
	// �y�䕔���̕`��
	void drawBase();

	// �\���F�̍X�V
	void updateDispColor();
	// �\���F�̎擾
	unsigned int getDispColor();

	// ��Ԃ��Ƃ�update����
	void updateWait();		// �o��O�ҋ@
	void updateAppear();	// �o�ꉉ�o
	void updateIdle();		// �o��ςݑҋ@
	void updateDecide();	// ���艉�o
		// ���艉�o�I���ς�
	void updateErase();	// (���̃{�^�����I�������)�����鉉�o
		// �����鉉�o�I���ς�

private:
	// �����o�[�֐��|�C���^
	void (PadUiItem::*m_updateFunc)() = &PadUiItem::updateWait;

	// ���o�����s�����߂ɂ�������O���t�B�b�N�ɕ`�悵�Ă��炻���`��
	int m_graphHandle;

	// �g���p�̃O���t�B�b�N
	int m_borderHandle;
	// �\���͈͂̋�`
	Rect m_rect;
	// �����̃t�H���g�n���h��
	int m_font;
	// �J�[�j���O
	int m_karning;

	// ���̍��ڂŌ���\��
	bool m_isDecideEnable;

	// �\���F
	int m_colorR;
	int m_colorG;
	int m_colorB;

	int m_alpha;

	double m_selectScale;		// �I������Ă��鎞�̃X�P�[��
	double m_unselectScale;		// �I������Ă��Ȃ����̃X�P�[��

	int m_index;		// �����I�ȊǗ��ԍ�
	const char* m_str;	// �{�^���ɕ\�����郁�b�Z�[�W

	bool m_isSelect;	// �I�����

	// ���o�֘A
	int m_frameCount;
	int m_startWait;	// �o��J�n�܂ł̃t���[����	-1�̏ꍇ�͐i�܂Ȃ�
	double m_scale;

	// ������\���p�̃f�[�^
	std::shared_ptr<EffectString>	m_pString;

	// �e�L�[���������Ƃ��Ɉړ������̃{�^���C���f�b�N�X
	// �ړ����Ȃ��ꍇ��-1
	int m_trgUp;	// ��L�[���g���K�[�����Ƃ��Ɉړ�����Item�̃C���f�b�N�X
	int m_repUp;	// ��L�[�̃��s�[�g�����͂��ꂽ�Ƃ��Ɉړ�����Item�̃C���f�b�N�X
	int m_trgDown;
	int m_repDown;
	int m_trgLeft;
	int m_repLeft;
	int m_trgRight;
	int m_repRight;

};


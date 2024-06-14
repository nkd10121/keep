#pragma once

#include "DxLib.h"

#ifdef _DEBUG
// �������׌v��
#define DISP_PROCESS
#endif

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

public:
	// �h���N���X�Ɍp������K�v�̂��鏈��
	virtual void startLoad() = 0;	// ���\�[�X�̃��[�h�J�n
	virtual bool isLoaded() const = 0;	// ���\�[�X�̃��[�h��������

	virtual void init() = 0;	// ������	���\�[�X�̃��[�h������ɌĂ΂��
	virtual void end() = 0;		// �V�[���I�����ɌĂ΂��	���\�[�X�̉���͂���

	virtual void update() = 0;	// ���\�[�X�̃��[�h�����ȍ~�Ă΂��	�t�F�[�h�����Ă΂��
	virtual void draw() = 0;

	// �t�F�[�h�����O�ʂɕ\��
	virtual void drawFront() {}
#ifdef _DEBUG
	// �f�o�b�O�\��(�őO�ʕ\��)
	virtual void drawDebug() {}
#endif
	// ���݂̃��[�h�i�����擾	0.0~1.0	�s���̏ꍇ�͕��̒l��Ԃ�
	virtual float getLoadProgress() const { return -1.0f; }

protected:
	// �h���N���X�쐬�ɗ��p���鏈��

	// �������ς�(init���Ă΂ꂽ)�`�F�b�N
	bool isInitialized() { return m_isInit; }

	// ���[�h���\�����s�����ǂ����ݒ�
	// ���[�h��1�b���x�ȏ㎞�Ԃ�������ꍇ��true����
	void setDispLoading(bool isDisp) { m_isDispLoading = isDisp; }

	// �t�F�[�h�ɂ�����t���[������ݒ�
	// �ݒ���s��Ȃ������ꍇ�̓f�t�H���g�̃t���[�����ɂȂ�
	// �t�F�[�h�C���̓f�t�H���g�X�s�[�h�ɂ��āA�V�[���I���O�ɕʂ̃t���[������ݒ肷�邱�Ƃ��\
	void setFadeFrame(int frame) { m_fadeTotalFrame = frame; }

	// �t�F�[�h������
	bool isFadingIn() const;	// �t�F�[�h�C����
	bool isFadingOut() const;	// �t�F�[�h�A�E�g��
	bool isFading() const { return isFadingIn() || isFadingOut(); }	// �t�F�[�h�C��or�A�E�g��

	// ���̃V�[���ɑJ�ڂ���
	// �����Ƀt�F�[�h�C���J�n����
	// �t�F�[�h���ɂ͌Ă΂Ȃ��悤��
	// nullptr�w��ŃQ�[���I��
	void setNextScene(SceneBase* pNext);

	// ���݂̃t�F�[�h�x����	0.0:���S�ɉ�ʌ����Ă���	1.0:��ʌ����Ă��Ȃ�
	float getFadeProgress() const;

public:
	// �p�����s��Ȃ�����	SceneManager����Ăяo���̂͂�����
	void initAll();	// �V�[���ʂ�init()�̑����ʂŕK�v�ȏ��������s��	
					// ����̓��[�h������̏���update()�ŌĂԂ̂�SceneManager()����͌Ă΂Ȃ�
	void endAll();	// �V�[���ʂ�end()�̑����ʂŕK�v�ȏ��������s��

	void updateAll();	// �V�[���ʂ�update()�̑����ʂŕK�v�ȏ��������s��
	void drawAll();		// �V�[���ʂ�draw()�̑����ʂŕK�v�ȏ��������s��

	bool isSceneEnd();	// ���݂̃V�[�����I�����Ď��̃V�[���ɑJ�ڂ���
	SceneBase* getNextScene() { return m_pNext; }	// �I����̑J�ڐ�V�[���擾	nullptr�ŃQ�[���I��

	void setFadeColor(unsigned int color) { m_fadeColor = color; }
	unsigned int getFadeColor() const { return m_fadeColor; }

	void setFadePlayerKind(int kind) { m_fadePlayerKind = kind; }
	int getFadePlayerKind() const { return m_fadePlayerKind; }

private:
	// �t�F�[�h�֘A
	void updateFade();
	void drawFade() const;

	// ���[�h���\��
	void drawLoading() const;

	// �}�E�X�J�[�\���\��
	void drawCursor() const;

	void startFadeIn();		// �t�F�[�h�C���J�n
	void startFadeOut();	// �t�F�[�h�A�E�g�J�n

	// �}�E�X�J�[�\���\���ݒ�
	void setDispCursor(bool isDisp) { m_isDispCursor = isDisp; }

private:

	int m_fadeMask;

	// �����������I������
	bool m_isInit;

	// �t�F�[�h�֘A����
	int m_fadeFrame;	// 0:�t�F�[�h�C������	=m_fadeTotalFrame:��ʐ^����
	int m_fadeTotalFrame;
	int m_fadeDir;

	// �t�F�[�h���o
	unsigned int m_fadeColor;
	int m_fadePlayerKind;


	// ���[�h���\�����s����
	bool m_isDispLoading;
	// ���[�h�t���[�����J�E���g
	int m_loadFrame;

	// �J�[�\���\��
	bool m_isDispCursor;

	// �V�[���J��
	bool m_isEnd;
	SceneBase* m_pNext;
	// �������׌v��
#ifdef DISP_PROCESS
	LONGLONG	m_updateTime;	// update�ɂ�����������(�~���b)
	LONGLONG	m_drawTime;		// draw�ɂ�����������(�~���b)
//	int	m_updateTime;	// update�ɂ�����������(�~���b)
//	int	m_drawTime;		// draw�ɂ�����������(�~���b)
#endif
};
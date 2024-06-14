#pragma once
#include "Vec2.h"
#include "Rect.h"

#include <memory>
#include <vector>

class PadUiItem;
class PadUi
{
public:
	PadUi();
	virtual ~PadUi();

	void setButtonGraph(int handle) { m_buttonGraph = handle; }

	int update();	// �����I�����ꂽ�t���[���ɂ��̃C���f�b�N�X��Ԃ�	����ȊO��-1
	void draw();

	// ���ڂ̒ǉ�	index��0����n�܂�ʂ��ԍ���z��
	void addItem(std::shared_ptr<PadUiItem> pItem);			// �ʂɐ����������̂�ǉ�
	void addItem(int index, const char* str, Rect rect);	// rect�w��
	void addItem(int index, const char* str, Vec2 center, int width, int height);	// ���S���W(Vec2)�A�������w��
	void addItem(int index, const char* str, int centerX, int centerY, int width, int height);	// ���S���W(x,y)�A�������w��

	// �e�{�^���̑J�ڐ�ݒ�	�ȒP�ݒ� �c�ɕ���UI�A���ɕ���UI���ȒP�ɐݒ肷��
	// �㉺���E�Ɉړ�����悤��UI�̏ꍇ�͌X�̃{�^���Ɏ����Őݒ肷��
	// addItem���I����Ă���s��
	// isLoop=true�̏ꍇ�[����t�̒[�Ƀ��[�v����
	void setupVArrange(bool isLoop);	// �c�ɕ���Ŕz�u���ꂽ�{�^���̑J�ڐݒ�
	void setupHArrange(bool isLoop);	// ���ɕ���Ŕz�u���ꂽ�{�^���̑J�ڐݒ�

	// UI�̒[�Ń��[�v���s�����̐ݒ�
	void setLoop(bool isLoop) { m_isLoop = isLoop; }

	// �����I�Ɏw�肵���ԍ���I����Ԃɂ���
	void setSelect(int index);

	// �I�𒆂̍��ڎ擾	�����I������Ă��Ȃ��ꍇ��-1
	int getSelectIndex();

	std::shared_ptr<PadUiItem> getItem(int index);

	//����\��
	bool isOperable() const;

	// ���ݑI������Ă��鍀�ڂŌ���ł��邩
	bool isDecideEnable();

private:
	std::vector<std::shared_ptr<PadUiItem>>	m_pItem;

	// �{�^���\���Ɏg�p����O���t�B�b�N
	int m_buttonGraph;

	// �[�ł̍��ڃ��[�v
	bool m_isLoop;

	// ���s�[�g����
	std::vector<int> m_repeatFrame;

	

	// ���o�p
	float m_sinRate;
};


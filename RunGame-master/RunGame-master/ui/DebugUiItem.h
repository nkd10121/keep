#pragma once
#include "Vec2.h"

class DebugUiItem
{
public:
	DebugUiItem(int index, Vec2 pos, const char* str);
	virtual ~DebugUiItem();

	void update();
	void draw();

	// �I����ԂɂȂ������ɌĂ΂�鏈��
	void OnSelect();
	// �I����ԂłȂ��Ȃ������ɌĂ΂�鏈��
	void OnUnselect();

	// �f�[�^�̎擾
	int getIndex() const { return m_index; }
	Vec2 getPos() const { return m_pos; }

	// ���ݑI������Ă��鍀�ڂ�
	bool isSelecting() const { return m_isSelect; }

private:
	int m_index;	// �Ǘ��ԍ�
	Vec2 m_pos;		// �\���ʒu
	const char* m_str;	// �\�����镶����

	bool m_isSelect;
};


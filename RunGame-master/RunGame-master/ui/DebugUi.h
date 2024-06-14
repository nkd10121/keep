#pragma once
#include <memory>
#include <vector>

class DebugUiItem;
class DebugUi
{
public:
	// �f�o�b�O���j���[�̍�����W���w�肷��
	DebugUi(int x = 0, int y = 0);
	virtual ~DebugUi();

	int update();	// �����I�����ꂽ�t���[���ɂ��̃C���f�b�N�X��Ԃ�	����ȊO��-1
	void draw();

	// ���ڂ̒ǉ�	index��0����n�܂�ʂ��ԍ���z��
	void addItem(int index, const char* str);

	// �����I�Ɏw�肵���ԍ���I����Ԃɂ���
	void setSelect(int index);

	// �I�𒆂̍��ڎ擾	�����I������Ă��Ȃ��ꍇ��-1
	int getSelectIndex();

private:
	std::vector<std::shared_ptr<DebugUiItem>>	m_pItem;

	// �㉺�ł̍��ڃ��[�v
	bool m_isLoop;

	// ���j���[�̍���ʒu
	int m_offsetX;
	int m_offsetY;

	// �㉺���s�[�g����
	int m_repeatUp;
	int m_repeatDown;
};


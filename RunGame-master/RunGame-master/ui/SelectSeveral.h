#pragma once
#include "Vec2.h"
#include <vector>
#include <memory>

class EffectPlayer;

// �������ڂ���1��I������UI���쐬
// �R���t�B�O��ʂł̌���I���ȂǂɎg�p����z��
class SelectSeveral
{
public:
	SelectSeveral();
	virtual ~SelectSeveral();

	void init(Vec2 center);
	void update();
	void draw();

	void addItem(const char* str, int value);
	// �����ݒ�(addItem,�����I����Ԃ�setSelect)���s������ɌĂ�
	void setup();

	// ������ԂőI������Ă��鍀�ڂ�����
	void setSelectIndex(int index);
	// value���珉����ԂőI������Ă��鍀�ڂ�����
	void setSelectValue(int value);

	void setActive(bool isActive);

	// �I���\�ȃA�C�e�����̎擾
	int getItemNum();
	// ���ݑI�����Ă���A�C�e���̔ԍ����擾
	int getSelectNo();

	// �I�����Ă��鍀�ڂɐݒ肵�Ă��鐔�l���擾
	int getSelectValue();
	int getValue(int index);

private:
	struct Item
	{
		const char* str;
		int value;
	};

private:
	// �I�����Ă��鍀�ڂ̕������ɍ��킹�ăJ�[�\���\���ʒu���X�V
	void updateCurorPos();

private:
	Vec2	m_center;
	int	m_selectNo;
	bool m_isActive;
	float m_cursorMoveX;

	std::vector<Item>	m_item;
	std::shared_ptr<EffectPlayer>	m_pCursorL;
	std::shared_ptr<EffectPlayer>	m_pCursorR;
};


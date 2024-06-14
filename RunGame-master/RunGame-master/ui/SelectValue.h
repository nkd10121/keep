#pragma once
#include "Vec2.h"
#include <memory>

class EffectPlayer;

// ���l��I������UI���쐬
// �R���t�B�O��ʂł̉��ʑI���ȂǂɎg�p����z��
class SelectValue
{
public:
	SelectValue();
	virtual ~SelectValue();

	void init(Vec2 center, int min, int max, int nowValue);
	void update();
	void draw();

	void setActive(bool isActive);
	int getValue() const { return m_value; }

private:

	float getValueRate();
	// �o�[�̉E�[X���W�擾
	int getBarEndX();
	// �A�C�R���\���ʒu�X�V
	void updateValueIconPos();
	// ���݂̉��ʁA�ω���������A�C�R���̏�Ԃ��X�V����
	// ���ʂ��������Ƃ���+1(>0),�������Ƃ���-1(<0),�f�t�H���g�̎���0���w��
	void updateValueIconAnim(int change);

private:
	Vec2	m_center;
	bool m_isActive;

	int m_value;	// ���݂̐��l
	// �l�͈̔�
	int m_min;
	int m_max;

	std::shared_ptr<EffectPlayer>	m_pCurrectValue;
	std::shared_ptr<EffectPlayer>	m_pCursorL;
	std::shared_ptr<EffectPlayer>	m_pCursorR;
};


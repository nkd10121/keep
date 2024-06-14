#pragma once
#include <memory>
#include "Vec2.h"
class ParticleManager;
class Particle
{
public:
	Particle(std::shared_ptr<ParticleManager> pManager);
	virtual ~Particle();

	void init();
	void update();
	void draw() const;

	bool isExist() { return (m_existFrame > 0); }

	// �悭�g���p�[�e�B�N������
	void createTest(Vec2 pos, int existFrame, unsigned int color);	// �����Ȃ��A���t���[���ŏ�����
	void createDamage(Vec2 pos, int existFrame, unsigned int color);	// �_���[�W���o�p�p�[�e�B�N������
	void createDeadEnemy(Vec2 pos, int existFrame, unsigned int color);	// �G���S���p�[�e�B�N������

	// �X�e�[�^�X���ڐݒ�
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setGravity(Vec2 gravity) { m_gravity = gravity; }
	void setGravity(float gravity) { m_gravity = Vec2{0,gravity}; }	// �������ւ̏d�͐ݒ�
	void setRadius(float radius) { m_radius = radius; }
	void setColor(unsigned int color) { m_color = color; }
	void setAlpha(int alpha) { m_alpha = alpha; }
	void setAlphaAcc(int alphaAcc) { m_alphaAcc = alphaAcc; }

	void setExistFrame(int frame) { m_existFrame = frame; }

	void setUseScroll(bool isScroll) { m_isScroll = isScroll; }

	// �X�e�[�^�X�擾
	Vec2 getPos() const { return m_pos; }
	Vec2 getVec() const { return m_vec; }

private:

	std::shared_ptr<ParticleManager>	m_pManager;

	Vec2 m_pos;		// �\���ʒu
	Vec2 m_vec;		// �����x
	Vec2 m_gravity;	// �d��
	float m_radius;	// �\�����a
	unsigned int m_color;	// �F
	int m_alpha;	// �����x
	int m_alphaAcc;	// �����x�ω���

	// ��������	0�ō폜
	int m_existFrame;

	// Manager�̎��X�N���[���ʂ𔽉f������
	bool m_isScroll;
};

#pragma once
#include <list>
#include <memory>
#include "Vec2.h"

class Particle;

class ParticleManager : public std::enable_shared_from_this<ParticleManager>
{
public:
	ParticleManager();
	virtual ~ParticleManager();

	void clear();
	void update();
	void draw();

	// ��ʃX�N���[��
	void setScroll(Vec2 scroll) { m_scroll = scroll; }
	Vec2 getScroll() const { return m_scroll; }

	// ���������p�[�e�B�N����ǉ�
	void add(std::shared_ptr<Particle> pParticle);

	// �e��p�[�e�B�N������


	// ���݂���p�[�e�B�N���̐�
	int getParticleNum() const;

private:
	std::list<std::shared_ptr<Particle>> m_pParticle;

	Vec2 m_scroll;
};


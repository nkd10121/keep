#include "ParticleManager.h"
#include "Particle.h"

namespace
{
	constexpr int kDamageParticleNum = 16;
	constexpr int kEnemyDeadParticleNum = 32;
}

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::clear()
{
}

void ParticleManager::update()
{
	for (auto& part : m_pParticle)
	{
		part->update();
	}
	// 使用済みパーティクルを削除
	m_pParticle.remove_if(
		[](auto& part) {
			return !part->isExist();
		});
}

void ParticleManager::draw()
{
	for (auto& part : m_pParticle)
	{
		part->draw();
	}
}

void ParticleManager::add(std::shared_ptr<Particle> pParticle)
{
	m_pParticle.push_back(pParticle);
}

int ParticleManager::getParticleNum() const
{
	return static_cast<int>(m_pParticle.size());
}


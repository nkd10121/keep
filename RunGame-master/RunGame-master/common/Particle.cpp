#include "Particle.h"
#include "DxLib.h"

#include "ParticleManager.h"

Particle::Particle(std::shared_ptr<ParticleManager> pManager):
	m_pManager(pManager),
	m_color(0xffffff),
	m_radius(0.0f),
	m_alpha(255),
	m_alphaAcc(0),
	m_existFrame(0),
	m_isScroll(true)
{
}

Particle::~Particle()
{
}

void Particle::init()
{
}

void Particle::update()
{
	if (!isExist())	return;
	m_vec += m_gravity;
	m_pos += m_vec;

	m_alpha += m_alphaAcc;
	if (m_alpha > 255)	m_alpha = 255;
	if (m_alpha < 0)	m_alpha = 0;

	m_existFrame--;
}

void Particle::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	Vec2 pos = m_pos;
	if (m_isScroll)	pos += m_pManager->getScroll();
	DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(m_radius), m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Particle::createTest(Vec2 pos, int existFrame, unsigned int color)
{
	m_pos = pos;
	m_vec = Vec2{ 0,0 };
	m_gravity = Vec2{ 0,0 };
	m_radius = GetRand(1) + 1.0f;
	m_color = color;
	m_existFrame = existFrame;
	m_alpha = 255;
	m_alphaAcc = -256 / m_existFrame;
}

void Particle::createDamage(Vec2 pos, int existFrame, unsigned int color)
{
	m_pos = pos;

	// ƒ‰ƒ“ƒ_ƒ€‚È•ûŒü‚Ö‚Ì‰‘¬‚ğİ’è
	float angle = GetRand(359) * DX_TWO_PI_F / 360.0f;
	float speed = 10.0f + GetRand(10);
	speed *= 0.1f;
	m_vec.x = cosf(angle) * speed;
	m_vec.y = sinf(angle) * speed;

	m_gravity = Vec2{ 0, 0.05f };
	m_radius = GetRand(1) + 1.0f;
	m_color = color;
	m_existFrame = existFrame;
	m_alpha = 255;
	m_alphaAcc = -256 / m_existFrame;
}

void Particle::createDeadEnemy(Vec2 pos, int existFrame, unsigned int color)
{
	m_pos = pos;

	// ƒ‰ƒ“ƒ_ƒ€‚È•ûŒü‚Ö‚Ì‰‘¬‚ğİ’è
	float angle = GetRand(359) * DX_TWO_PI_F / 360.0f;
	float speed = 20.0f + GetRand(20);
	speed *= 0.1f;
	m_vec.x = cosf(angle) * speed;
	m_vec.y = sinf(angle) * speed;

	m_gravity = Vec2{ 0, 0.05f };
	m_radius = GetRand(2) + 2.0f;
	m_color = color;
	m_existFrame = existFrame;
	m_alpha = 255;
	m_alphaAcc = -256 / m_existFrame;
}
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

	// 画面スクロール
	void setScroll(Vec2 scroll) { m_scroll = scroll; }
	Vec2 getScroll() const { return m_scroll; }

	// 生成したパーティクルを追加
	void add(std::shared_ptr<Particle> pParticle);

	// 各種パーティクル生成


	// 存在するパーティクルの数
	int getParticleNum() const;

private:
	std::list<std::shared_ptr<Particle>> m_pParticle;

	Vec2 m_scroll;
};


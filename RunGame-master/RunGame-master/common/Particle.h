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

	// よく使うパーティクル生成
	void createTest(Vec2 pos, int existFrame, unsigned int color);	// 動かない、一定フレームで消える
	void createDamage(Vec2 pos, int existFrame, unsigned int color);	// ダメージ演出用パーティクル生成
	void createDeadEnemy(Vec2 pos, int existFrame, unsigned int color);	// 敵死亡時パーティクル生成

	// ステータス直接設定
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setGravity(Vec2 gravity) { m_gravity = gravity; }
	void setGravity(float gravity) { m_gravity = Vec2{0,gravity}; }	// 下方向への重力設定
	void setRadius(float radius) { m_radius = radius; }
	void setColor(unsigned int color) { m_color = color; }
	void setAlpha(int alpha) { m_alpha = alpha; }
	void setAlphaAcc(int alphaAcc) { m_alphaAcc = alphaAcc; }

	void setExistFrame(int frame) { m_existFrame = frame; }

	void setUseScroll(bool isScroll) { m_isScroll = isScroll; }

	// ステータス取得
	Vec2 getPos() const { return m_pos; }
	Vec2 getVec() const { return m_vec; }

private:

	std::shared_ptr<ParticleManager>	m_pManager;

	Vec2 m_pos;		// 表示位置
	Vec2 m_vec;		// 加速度
	Vec2 m_gravity;	// 重力
	float m_radius;	// 表示半径
	unsigned int m_color;	// 色
	int m_alpha;	// 透明度
	int m_alphaAcc;	// 透明度変化量

	// 生存期間	0で削除
	int m_existFrame;

	// Managerの持つスクロール量を反映させる
	bool m_isScroll;
};

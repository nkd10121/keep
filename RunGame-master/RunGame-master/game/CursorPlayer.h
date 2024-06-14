#pragma once
#include "Vec2.h"
#include <memory>

class EffectPlayer;
class ParticleManager;
// カーソルとして使用するプレイヤー
class CursorPlayer
{
public:
	CursorPlayer();
	virtual ~CursorPlayer();

	// パーティクル表示	設定しなくても動く(パーティクルは表示されない)
	void setParticle(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	void update();
	void draw();

	// 位置を直接設定	主に初期化に使用
	void setPos(Vec2 pos);
	// 対象位置を設定
	void setTarget(Vec2 target);
	// 種類を設定
	void setPlayerKind(int kind);

private:
	// 移動軌跡パーティクル生成
	void createMoveParticle();

private:

	// 表示用
	std::shared_ptr<EffectPlayer>	m_pCursor;
	// パーティクル
	std::shared_ptr<ParticleManager>	m_pParticle;

//	Vec2 m_pos;	// 現在位置
	Vec2 m_startPos;	// 移動開始位置
	Vec2 m_targetPos;	// 移動終了位置

	int m_moveFrame;
};


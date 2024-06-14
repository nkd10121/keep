#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <memory>

class Bg;
class EffectString;
class PadUi;
class EffectPlayer;
class CursorPlayer;
class Telop;
class ParticleManager;
class SceneMainMenu : public SceneBase
{
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

#ifdef _DEBUG
	virtual void drawDebug() override;
#endif

private:
	// UIにボタン情報を追加
	void addUiItem(int index);

private:
	// 背景演出
	std::shared_ptr<Bg>	m_pBg;
	// タイトル文字列
	std::shared_ptr<EffectString>	m_pTitle;
	// ボタンUI
	std::shared_ptr<PadUi>	m_pUi;
	// 説明テロップ
	std::shared_ptr<Telop>	m_pTelop;
	// カーソル(プレイヤーのグラフィック使用)
	std::shared_ptr<CursorPlayer>	m_pCursor;
	// パーティクル演出
	std::shared_ptr<ParticleManager>	m_pParticle;

	// グラフィック
	int m_uiBorder;

	// カーソルの状態管理
	Vec2	m_cursorPos;		// 現在位置
};


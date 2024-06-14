#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <memory>
#include <vector>

class EffectString;
class PadUi;
class EffectPlayer;
class ParticleManager;
class Bg;
class Telop;
class SceneSelectPlayerNum : public SceneBase
{
public:
	SceneSelectPlayerNum();
	virtual ~SceneSelectPlayerNum() {}

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
	// シーケンス別update処理
	void updateSelect();	// 人数選択メイン
	void updateOut();		// 切り替え演出


	// プレイヤー変更時のパーティクル演出生成
	void createKindChangeParticle(Vec2 iconPos, int nextKind);


private:

	void (SceneSelectPlayerNum::*m_updateFunc)() = &SceneSelectPlayerNum::updateSelect;

	// 背景演出
	std::shared_ptr<Bg>	m_pBg;
	// タイトル文字列
	std::shared_ptr<EffectString>	m_pTitle;
	// ボタンUI
	std::shared_ptr<PadUi>	m_pUi;
	// キャラクターアイコン
	using IconVector = std::vector<std::shared_ptr<EffectPlayer>>;
	std::vector<IconVector>	m_pPlayerIcon;
	// パーティクル演出
	std::shared_ptr<ParticleManager>	m_pParticle;
	// 説明テロップ
	std::shared_ptr<Telop>	m_pTelop;

	// 選択しているプレイヤーの種類
	std::vector<int>	m_selectPlayerKind;

	// 選択されていないアイコンのアルファ
	int m_iconAlpha;

	// 決定後
	int m_decidePlayerNum;
	int m_frameCount;
};


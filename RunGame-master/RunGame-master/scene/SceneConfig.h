#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <memory>

class EffectPlayer;
class EffectString;
class Bg;
class PadUi;
class Telop;
class CursorPlayer;
class ParticleManager;
class SelectSeveral;
class SelectValue;
class SceneConfig : public SceneBase
{
public:
	SceneConfig();
	virtual ~SceneConfig();

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
	void addUiItem(int index);

	// 選択されている項目別の処理
	void procLanguage();
	void procBgmVol();
	void procSeVol();
	void procVibration();
	void procFullScreen();

	// 各設定項目の内容表示
	void drawEraseData();

	// 言語変更Aボタン待ち
	bool isChangeLanguageWait();
	// ウインドウモード変更Aボタン待ち
	bool isChangeWindowModeWait();

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
	// カーソルの状態管理
	Vec2	m_cursorPos;		// 現在位置

	// コンフィグ画面で使用するプレイヤーの種類
	int m_playerKind;

	// 言語設定UI
	std::shared_ptr<SelectSeveral>	m_pItemLanguage;
	// 音量設定表示UI
	std::shared_ptr<SelectValue>	m_pItemBgmVol;
	std::shared_ptr<SelectValue>	m_pItemSeVol;
	// 振動設定表示UI
	std::shared_ptr<SelectSeveral>	m_pItemVibration;
	// フルスクリーン設定表示UI
	std::shared_ptr<SelectSeveral>	m_pItemFullScreen;

	// 設定変更確認表示
	std::shared_ptr<EffectString>	m_pChangeLanguage;
	std::shared_ptr<EffectString>	m_pChangeFullScreen;
};


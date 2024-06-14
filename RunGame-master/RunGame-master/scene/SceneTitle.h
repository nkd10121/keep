#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <list>
#include <memory>

class EffectPlayer;
class EffectString;
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;


private:
	// 背景演出用のプレイヤー
	struct TitlePlayer
	{
		Vec2 pos;
		bool isExist = false;
	};

private:
	// シーケンスごとのupdate処理

	void updateLoadWait();
	void updateTitleAppear();	// タイトル登場演出
	void updateWait();			// プレイヤーの入力待ち

	// タイトルロゴグラフィックの生成
	void createLogoGraph();

	// タイトルロゴの表示
	void drawTitleLogo();

	// 背景演出
	void drawBg();

	// タイトル演出終了
	bool isTitleAppearEnd();

private:
	// シーケンス別update処理
//	void (SceneTitle::*m_updateFunc)() = &SceneTitle::updateTitleAppear;
	void (SceneTitle::* m_updateFunc)() = &SceneTitle::updateLoadWait;

	// 背景スクリーン
	int m_bgScreen;
	// グラフィックリソース
	int m_bgTile;

	// タイトルロゴ情報
	int m_titleFontHandle;
	int m_titleGraph;
	int m_titleWidth;

	int m_loadFrameCount;
	// タイトルロゴ登場演出
	int m_titleFrameCount;
	// 背景スクロール演出
	int m_bgScroll;
	// デモプレイ開始待ち時間
	int m_demoWaitFrame;

	// ボタンを押してね！テキスト
	std::shared_ptr<EffectString>	m_pText;

	// 演出用プレイヤー
	std::list<std::shared_ptr<EffectPlayer>>	m_pPlayer;
};


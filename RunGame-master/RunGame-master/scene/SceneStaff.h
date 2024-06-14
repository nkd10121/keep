#pragma once
#include "SceneBase.h"
#include <memory>

class EffectString;
class Bg;
class Telop;
class SceneStaff : public SceneBase
{
public:
	SceneStaff();
	virtual ~SceneStaff();

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
	// 背景演出
	std::shared_ptr<Bg>	m_pBg;
	// タイトル文字列
	std::shared_ptr<EffectString>	m_pTitle;
	// 説明テロップ
	std::shared_ptr<Telop>	m_pTelop;
};


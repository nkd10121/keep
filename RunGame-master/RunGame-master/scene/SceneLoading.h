#pragma once
#include "SceneBase.h"
#include <memory>

class Bg;

class SceneLoading : public SceneBase
{
public:
	SceneLoading();
	virtual ~SceneLoading();

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

#ifdef _DEBUG
	// デバッグ表示(最前面表示)
	virtual void drawDebug() override;
#endif

private:

	int m_frameCount;
	// 背景演出
	std::shared_ptr<Bg>	m_pBg;
};


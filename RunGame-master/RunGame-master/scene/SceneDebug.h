#pragma once
#include "SceneBase.h"

#include <memory>

class DebugUi;

class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {}

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;


private:
	
	int m_frameCount;

//	std::vector<std::shared_ptr<DebugUiItem>>	m_pItem;
	std::shared_ptr<DebugUi>	m_pUi;
};
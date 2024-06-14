#pragma once
#include "SceneBase.h"

#include <memory>

class DispRecord;
class SceneTest : public SceneBase
{
public:
	SceneTest();
	virtual ~SceneTest() {}

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

private:
	int m_frameCount;

	std::shared_ptr<DispRecord>	m_pRecord;

	int m_maskHandle;
};
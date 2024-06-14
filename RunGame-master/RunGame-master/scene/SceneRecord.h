#pragma once
#include "SceneBase.h"
#include <memory>

class DispRecord;
//class EffectString;
class Bg;
class Telop;
class SceneRecord : public SceneBase
{
public:
	SceneRecord();
	virtual ~SceneRecord() {}

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

private:
	// îwåiââèo
	std::shared_ptr<Bg>	m_pBg;

	std::shared_ptr<DispRecord>	m_pRecord;
	std::shared_ptr<Telop>	m_pTelop;
};


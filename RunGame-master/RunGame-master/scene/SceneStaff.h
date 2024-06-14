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
	// �w�i���o
	std::shared_ptr<Bg>	m_pBg;
	// �^�C�g��������
	std::shared_ptr<EffectString>	m_pTitle;
	// �����e���b�v
	std::shared_ptr<Telop>	m_pTelop;
};


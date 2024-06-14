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
	// �V�[�P���X��update����
	void updateSelect();	// �l���I�����C��
	void updateOut();		// �؂�ւ����o


	// �v���C���[�ύX���̃p�[�e�B�N�����o����
	void createKindChangeParticle(Vec2 iconPos, int nextKind);


private:

	void (SceneSelectPlayerNum::*m_updateFunc)() = &SceneSelectPlayerNum::updateSelect;

	// �w�i���o
	std::shared_ptr<Bg>	m_pBg;
	// �^�C�g��������
	std::shared_ptr<EffectString>	m_pTitle;
	// �{�^��UI
	std::shared_ptr<PadUi>	m_pUi;
	// �L�����N�^�[�A�C�R��
	using IconVector = std::vector<std::shared_ptr<EffectPlayer>>;
	std::vector<IconVector>	m_pPlayerIcon;
	// �p�[�e�B�N�����o
	std::shared_ptr<ParticleManager>	m_pParticle;
	// �����e���b�v
	std::shared_ptr<Telop>	m_pTelop;

	// �I�����Ă���v���C���[�̎��
	std::vector<int>	m_selectPlayerKind;

	// �I������Ă��Ȃ��A�C�R���̃A���t�@
	int m_iconAlpha;

	// �����
	int m_decidePlayerNum;
	int m_frameCount;
};


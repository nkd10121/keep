#include "SceneLoading.h"
#include "DxLib.h"

#include "Sound.h"
#include "Font.h"
#include "Bg.h"

#ifdef _DEBUG
#include "SceneDebug.h"
#else
#include "SceneTitle.h"
#endif

namespace
{
	// ���[�h�I����Ă��Ă��ŒႱ�̃t���[�����͑҂�
	constexpr int kWaitFrameMin = 60;
}

SceneLoading::SceneLoading():
	m_frameCount(0)
{
	// �V�[���ݒ�
	setDispLoading(false);	// ���[�h���\�����s��Ȃ�

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

SceneLoading::~SceneLoading()
{
}

void SceneLoading::startLoad()
{
	// �񓯊��ǂݍ��݂��J�n����
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// �f�t�H���g�ɖ߂�
	SetUseASyncLoadFlag(false);
}

bool SceneLoading::isLoaded() const
{
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneLoading::init()
{
	// �w�i���o
	m_pBg->setPlayerInterval(4);
	m_pBg->setPlayerCreateNum(1);
}

void SceneLoading::end()
{
	// �t�F�[�h�����������ƂɕK�v�ȏ��̎��W���s��

	// �T�E���h�̏����W
	Sound::getInstance().collectData();
	// �t�H���g�̏����W
	Font::collectData();
}

void SceneLoading::update()
{
	m_pBg->update();

	if (getFadeProgress() > 0.0f)
	{
		return;
	}

	// ���[�h���̃��\�[�X���Ȃ����m�F
	bool isLoading = false;
	if (!Sound::getInstance().isLoaded())
	{
	//	printfDx("sound loading...\n");
		isLoading = true;
	}
	if (!Font::isLoaded())
	{
	//	printfDx("font loading...\n");
		isLoading = true;
	}

	m_frameCount++;
//	printfDx("m_frameCount = %d\n", m_frameCount);
	if( (m_frameCount >= kWaitFrameMin) &&	// ���[�h���I����Ă���莞�ԕ\��
		(!isLoading) )
	{
#ifdef _DEBUG
		setNextScene(new SceneDebug);
#else
		setNextScene(new SceneTitle);
#endif
	}
}

void SceneLoading::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();
	DrawString(64 + GetRand(4), 64 + GetRand(4), "Loading...", 0xffffff);
}

#ifdef _DEBUG
void SceneLoading::drawDebug()
{
	DrawString(8, 8, "SceneLoading", 0xffffff);
}
#endif

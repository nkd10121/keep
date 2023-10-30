#include <DxLib.h>

#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "StageSelect.h"

void TitleScene::FadeInUpdate(Input&)
{
	frame_--;
	if (frame_ <= 0)
	{
		//�t�F�[�h�C�����I��������Ԃ�J�ڂ���
		//���̑J�ڐ�
		updateFunc_ = &TitleScene::NormalUpdate;
		drawFunc_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		//����Enter�L�[�������ꂽ��t�F�[�h�C�����n�߂�
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		frame_ = 0;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	frame_++;
	if (frame_ >= 60)
	{
		//�t�F�[�h�A�E�g���I�������Scene��ς���
		manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//�ʏ�̕`��
	DrawString(100, 100, "TitleScene", 0xffffff);

	//�t�F�[�h�Ö�
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(100, 100, "TitleScene", 0xffffff);
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager)
{
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	OutputDebugString("�^�C�g���V�[����delete����܂���\n");
}

void TitleScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	(this->*drawFunc_)();
}

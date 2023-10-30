#include "StageSelect.h"
#include "../Input.h"
#include "GamePlayingScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void StageSelect::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &StageSelect::NormalUpdate;
		drawFunc_ = &StageSelect::NormalDraw;
	}
}

void StageSelect::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &StageSelect::FadeOutUpdate;
		drawFunc_ = &StageSelect::FadeDraw;
	}
}

void StageSelect::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		manager_.ChangeScene(std::make_shared<GamePlayingScene>(manager_));
	}
}

void StageSelect::FadeDraw()
{
	//í èÌÇÃï`âÊ
	DrawString(100, 100, "StageSelectScene", 0xffffff);


	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void StageSelect::NormalDraw()
{
	DrawString(100, 100, "StageSelectScene", 0xffffff);
}

StageSelect::StageSelect(SceneManager& mgr) : Scene(mgr)
{
	updateFunc_ = &StageSelect::FadeInUpdate;
	drawFunc_ = &StageSelect::FadeDraw;
	frame_ = 60;
}

StageSelect::~StageSelect()
{

}

void StageSelect::Update(Input& input)
{
	(this->*updateFunc_)(input);

}

void StageSelect::Draw()
{
	(this->*drawFunc_)();
}

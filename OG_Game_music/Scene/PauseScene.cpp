#include "PauseScene.h"
#include "DxLib.h"
#include "../Input.h"
#include "../Application.h"
#include "SceneManager.h"

constexpr int apper_interval = 30;

void PauseScene::AppearUpdate(Input&)
{
	++frame_;
	if (frame_ == apper_interval)
	{
		updateFunc_ = &PauseScene::NormalUpdate;
		drawFunc_ = &PauseScene::NormalDraw;
	}
}

void PauseScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("pause"))
	{
		updateFunc_ = &PauseScene::DisappearUpdate;
		drawFunc_ = &PauseScene::ExpandDraw;

	}
}

void PauseScene::DisappearUpdate(Input&)
{
	--frame_;
	if (frame_ == 0)
	{
		manager_.popScene();

	}
}

void PauseScene::ExpandDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	int halfHeight = (size.h - 100) / 2;
	int centerY = size.h / 2;

	float rate = static_cast<float>(frame_) / static_cast<float> (apper_interval);	//Œ»Ý‚ÌŽžŠÔ‚ÌŠ„‡(0.0 ` 1.0)

	int currntHalfHeight = rate * halfHeight;

	//”–‚¢ŽlŠp‚ð•\Ž¦
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	DrawBox(50, centerY - currntHalfHeight, size.w - 50, centerY + currntHalfHeight, 0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//”’ˆä˜gü‚ð•\Ž¦
	DrawBox(50, centerY - currntHalfHeight, size.w - 50, centerY + currntHalfHeight, 0xffffff, false);
}

void PauseScene::NormalDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();


	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	DrawBox(50, 50, size.w - 50, size.h - 50, 0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(100, 100, "pauseScene", 0xffffff);
	DrawBox(50, 50, size.w - 50, size.h - 50, 0xffffff, false);
}

PauseScene::PauseScene(SceneManager& manager) : Scene(manager)
{
	updateFunc_ = &PauseScene::AppearUpdate;
	drawFunc_ = &PauseScene::ExpandDraw;
}

void PauseScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void PauseScene::Draw()
{

	(this->*drawFunc_)();

}

#include "StageSelect.h"
#include "../Util/Input.h"
#include "../Util/Game.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include <DxLib.h>

#include "../DrawBGparts.h"

#include "../Player.h"
#include "../TargetCircle.h"
#include "../Util/Col.h"

#include "Stage/StageTutorial.h"
#include "Stage/Stage2.h"
#include "Stage/Stage1.h"

namespace
{
	//フェードイン、フェードアウトにかかる時間
	constexpr int kFadeFrame = 30;

	constexpr int kBGnum = 10;
}

void StageSelect::SetNextInfo(int kindNum)
{
	if (kindNum == 0)
	{
		m_manager.sManager.PlayBGM("Tutorial", true);
		next = nTutorial;
	}
	else if (kindNum == 1)
	{
		m_manager.sManager.PlayBGM("stage1", true);
		next = nStage1;
	}
	else if (kindNum == 2)
	{
		m_manager.sManager.PlayBGM("stage2", true);
		next = nStage2;
	}
}

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

	player->Update(input);
	playerCol = player->GetColRect();

	if (input.IsTriggered("pause"))
	{
		m_manager.sManager.PlaySE("enterSE");

		m_manager.PushScene(std::make_shared<PauseScene>(m_manager));
	}

	for (int i = 0; i < target.size(); i++)
	{
		if (target[i])
		{
			if (playerCol.IsCollisionCircle(target[i]->GetColRect()) && input.IsTriggered("OK"))
			{
				target[i]->Flag();

				updateFunc_ = &StageSelect::FadeOutUpdate;
				drawFunc_ = &StageSelect::FadeDraw;
			}
		}
	}
}

void StageSelect::FadeOutUpdate(Input& input)
{
	frame_++;
	m_manager.sManager.FadeOutBGM("Tutorial", frame_);
	m_manager.sManager.FadeOutBGM("stage1", frame_);
	m_manager.sManager.FadeOutBGM("stage2", frame_);
	if (frame_ >= kFadeFrame)
	{
		if (next == nTutorial)
		{
			m_manager.ChangeScene(std::make_shared<StageTutorial>(m_manager));
		}
		if (next == nStage1)
		{
			m_manager.ChangeScene(std::make_shared<Stage1>(m_manager));
		}
		if (next == nStage2)
		{
			m_manager.ChangeScene(std::make_shared<Stage2>(m_manager));
		}
	}
}

void StageSelect::FadeDraw()
{
	//通常の描画

#ifdef _DEBUG
	DrawString(0, 0, "StageSelectScene", 0xffffff);
#endif
	int alpha = 255 * static_cast<float>(frame_) / (float)kFadeFrame;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void StageSelect::NormalDraw()
{

#ifdef _DEBUG
	DrawString(0, 0, "StageSelectScene", 0xffffff);
#endif

}

StageSelect::StageSelect(SceneManager& mgr) :
	Scene(mgr)
{

	parts.resize(kBGnum);

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i] = new DrawBGparts;
		parts[i]->Init(true);
	}

	player = new Player;
	player->Init(false);

	target.resize(3);
	//チュートリアルに行く円
	CreateTargetCircle(Game::kScreenWidth / 8 * 5, Game::kScreenHeight / 4,1);
	//ステージ1に行く円
	CreateTargetCircle(Game::kScreenWidth / 8 * 7, Game::kScreenHeight / 4,1);
	//ステージ2に行く円
	CreateTargetCircle(Game::kScreenWidth / 8 * 5, Game::kScreenHeight / 4 * 3,1);

	updateFunc_ = &StageSelect::FadeInUpdate;
	drawFunc_ = &StageSelect::FadeDraw;
	frame_ = 60;

}

StageSelect::~StageSelect()
{
	delete player;
	player = nullptr;

	for (int i = 0; i < target.size(); i++)
	{
		if (target[i])
		{
			delete target[i];
			target[i] = nullptr;
		}
	}
}

void StageSelect::Update(Input& input)
{
	nextLog = next;
	next = No;

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}


	for (int i = 0; i < target.size(); i++)
	{
		if (target[i])
		{
			target[i]->Update();

			if (playerCol.IsCollisionCircle(target[i]->GetColRect()))
			{
				target[i]->Big();
				target[i]->Rotation();

				SetNextInfo(i);
			}
		}
	}

	if (next != No)
	{
		expandFrame++;
	}
	else
	{
		expandFrame = 0;
	}

	if (next == No && nextLog == nTutorial)
	{
		isSoundFade = true;
	}
	if (next == No && nextLog == nStage1)
	{
		isSoundFade = true;
	}
	if (next == No && nextLog == nStage2)
	{
		isSoundFade = true;
	}

	if (isSoundFade)
	{
		soundFadeFrame++;
		m_manager.sManager.FadeOutBGM("Tutorial",soundFadeFrame);
		m_manager.sManager.FadeOutBGM("stage1",soundFadeFrame);
		m_manager.sManager.FadeOutBGM("stage2",soundFadeFrame);

		if (soundFadeFrame > 30)
		{
			isSoundFade = false;
			soundFadeFrame = 0;
		}
	}


	(this->*updateFunc_)(input);
}

void StageSelect::Draw()
{

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}


	for (int i = 0; i < target.size(); i++)
	{
		if (target[i])
		{
			target[i]->Draw();
		}
	}

	player->Draw();

	if (next == nTutorial)
	{
		m_manager.gManager.Draw(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1.0f, 0.0f, "stageTutorialDetail");
	}

	if (next == nStage1)
	{
		m_manager.gManager.Draw(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1.0f, 0.0f, "stage1Detail");
	}

	if (next == nStage2)
	{
		m_manager.gManager.Draw(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1.0f, 0.0f, "stage2Detail");
	}

	(this->*drawFunc_)();
}

void StageSelect::CreateTargetCircle(int x, int y,int handleNum)
{
	for (int i = 0; i < target.size(); i++)
	{
		if (!target[i])
		{
			target[i] = new TargetCircle;
			target[i]->Init(x, y,handleNum);
			return;
		}
	}
}
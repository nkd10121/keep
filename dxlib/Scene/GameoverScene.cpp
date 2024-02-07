#include <DxLib.h>
#include "../Util/Input.h"
#include "../Util/Game.h"
#include "GameoverScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "../DrawBGparts.h"

#include "../Efect/Efects.h"
#include "../Efect/DashEfect.h"
#include "../AfterImagePlayer.h"

#include "Stage/Stage2.h"
#include "Stage/Stage1.h"
#include "Stage/StageTutorial.h"

namespace
{
	//フェードイン、フェードアウトにかかる時間
	constexpr int kFadeFrame = 30;

	constexpr int kButtonFirstPos = 780;
	constexpr int kButtonSecondPos = 860;

	constexpr int kPlayerPosX = 296;
	constexpr int kPlayerPosY = 360;

	constexpr int kBGnum = 12;
	constexpr int kEfectNum = 32;

	constexpr int kButtonMoveSpeed = 24;
}

GameoverScene::GameoverScene(SceneManager& mgr) :
	Scene(mgr), 
	m_frame(0),
	retryButtonX(kButtonFirstPos),
	returnButtonX(kButtonSecondPos),
	m_playerPos(kPlayerPosX, kPlayerPosY),
	isRevival(false),
	deathAnimationFlag(false)
{
	parts.resize(kBGnum);

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i] = new DrawBGparts;
		parts[i]->Init(false);
	}

	afterImage.resize(kEfectNum);


	handle[0] = LoadGraph("data/player/player0.png");
	handle[1] = LoadGraph("data/player/player1.png");
	handle[2] = LoadGraph("data/player/player2.png");
	handle[3] = LoadGraph("data/player/player3.png");

	updateFunc_ = &GameoverScene::FadeInUpdate;
	drawFunc_ = &GameoverScene::FadeDraw;

	fadeFrame = 60;
}

GameoverScene::~GameoverScene()
{
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			delete afterImage[i];
			afterImage[i] = nullptr;
		}
	}
}

void GameoverScene::Update(Input& input)
{
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}

	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!afterImage[i]->isExist())
			{
				//メモリを解放する
				delete afterImage[i];
				afterImage[i] = nullptr;	//使っていないとわかるように
			}
		}
	}

	if (isRevival == true)
	{
		m_frame++;

		//200フレーム(ダッシュする前)までは位置を補正
		if (m_frame <= 200)
		{
			m_playerPos = { kPlayerPosX,kPlayerPosY };
		}

		//回復中は震えるように
		if (m_frame >= 30)
		{
			if (m_frame < 120)
			{
				offset = { static_cast<float>(GetRand(4) - 2),static_cast<float>(GetRand(4) - 2) };
				m_playerPos += offset;
			}
		}

		//ダッシュ前の溜め中も震えるように
		if (m_frame >= 160)
		{
			if (m_frame < 200)
			{
				offset = { static_cast<float>(GetRand(4) - 2),static_cast<float>(GetRand(4) - 2) };
				m_playerPos += offset;
			}
		}

		//ダッシュし始める
		if (m_frame >= 200)
		{
			m_playerPos.x += 32;
		}

		//回復を始めたときにSEがなるように
		if (m_frame == 20)
		{
			m_manager.sManager.PlaySE("RevivalSE");

		}

	}


	if (m_frame >= 200)
	{
		updateFunc_ = &GameoverScene::FadeOutUpdate;
		drawFunc_ = &GameoverScene::FadeDraw;
	}

	if (m_frame == 200)
	{
		for (int i = 0; i < afterImage.size(); i++)
		{
			CreateAfterImage(m_playerPos);
		}
	}

	(this->*updateFunc_)(input);
}

void GameoverScene::Draw()
{
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}

	//残像の描画
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Draw();
		}
	}

	m_manager.Draw(static_cast<float>(retryButtonX), static_cast<float>(400), 1.0, 0, "Button1");
	DrawStringToHandle(retryButtonX + 148, 220, "リトライ", 0xffffff, m_manager.ReturnFontHandle());
	m_manager.Draw(static_cast<float>(returnButtonX), static_cast <float>(680), 1.0, 0, "Button3");
	DrawStringToHandle(returnButtonX + 148, 500, "タイトルへ", 0xffffff, m_manager.ReturnFontHandle());

	DrawBox(m_playerPos.x - 16, m_playerPos.y - 16, m_playerPos.x + 16, m_playerPos.y + 16, 0x004646, true);

	if (isRevival == true)
	{
		if (m_frame >= 120)
		{
			DrawRotaGraph(m_playerPos.x, m_playerPos.y, 1.0f, 0.0f, handle[0], true);
		}
		else if (m_frame >= 90)
		{
			DrawRotaGraph(m_playerPos.x, m_playerPos.y, 1.0f, 0.0f, handle[1], true);
		}
		else if (m_frame >= 60)
		{
			DrawRotaGraph(m_playerPos.x, m_playerPos.y, 1.0f, 0.0f, handle[2], true);
		}
		else if (m_frame >= 30)
		{
			DrawRotaGraph(m_playerPos.x, m_playerPos.y, 1.0f, 0.0f, handle[3], true);
		}
	}

	if (deathAnimationFlag == true)
	{
		m_frame++;
		int endY = m_frame * 128;

		DrawBox(m_playerPos.x - 32, 0, m_playerPos.x + 32, endY, 0xff00ff, true);

		if (endY /2 >= Game::kScreenHeight)
		{
			updateFunc_ = &GameoverScene::FadeOutUpdate;
			drawFunc_ = &GameoverScene::FadeDraw;
		}
	}

	(this->*drawFunc_)();
}

void GameoverScene::CreateAfterImage(Vec2 pos )
{
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (!afterImage[i])
		{
			afterImage[i] = new AfterImagePlayer;
			afterImage[i]->Init(pos, { 1,0 }, GetRand(4) + 4, true);
			return;
		}
	}
}

void GameoverScene::CreateDashEfect(Vec2 pos, bool isLastHit)
{
	for (int i = 0; i < efects.size(); i++)
	{
		if (!efects[i])
		{
			efects[i] = new DashEfect;
			efects[i]->Init(pos, isLastHit);
			return;
		}
	}
}

void GameoverScene::FadeInUpdate(Input& input)
{
	fadeFrame--;
	if (fadeFrame <= 0)
	{
		updateFunc_ = &GameoverScene::NormalUpdate;
		drawFunc_ = &GameoverScene::NormalDraw;
	}
}

void GameoverScene::NormalUpdate(Input& input)
{
	if (isRevival)
		return;

	if (nowButton == Retry)
	{
		if (retryButtonX > kButtonFirstPos)
		{
			retryButtonX -= kButtonMoveSpeed;
		}
	}
	else
	{
		//右に動かす
		if (retryButtonX < kButtonSecondPos)
		{
			retryButtonX += kButtonMoveSpeed;
		}
	}

	if (nowButton == Return)
	{
		if (returnButtonX > kButtonFirstPos)
		{
			returnButtonX -= kButtonMoveSpeed;
		}
	}
	else
	{
		//右に動かす
		if (returnButtonX < kButtonSecondPos)
		{
			returnButtonX += kButtonMoveSpeed;
		}
	}

	if (input.IsTriggered("UP"))
	{
		if (nowButton == Return)
		{
			nowButton = Retry;
		}
	}

	if (input.IsTriggered("DOWN"))
	{
		if (nowButton == Retry)
		{
			nowButton = Return;
		}
	}

	if (input.IsTriggered("OK") && nowButton == Retry)
	{
		isRevival = true;
	}

	if (input.IsTriggered("OK") && nowButton == Return)
	{
		deathAnimationFlag = true;
		m_manager.sManager.PlaySE("deathSE");

	}
}

void GameoverScene::FadeOutUpdate(Input& input)
{
	fadeFrame++;
	if (fadeFrame >= kFadeFrame)
	{
		if (nowButton == Retry)
		{
			if (m_manager.logScene == m_manager.stage1)
			{
				m_manager.ChangeScene(std::make_shared<Stage1>(m_manager));
			}
			else if (m_manager.logScene == m_manager.stage2)
			{
				m_manager.ChangeScene(std::make_shared<Stage2>(m_manager));
			}
			else if (m_manager.logScene == m_manager.StageTutorial)
			{
				m_manager.ChangeScene(std::make_shared<StageTutorial>(m_manager));
			}
		}
		else if (nowButton == Return)
		{
			m_manager.ChangeScene(std::make_shared<TitleScene>(m_manager));
		}
	}
}

void GameoverScene::FadeDraw()
{
#ifdef _DEBUG
	DrawString(0, 0, "GameoverScene", 0xffffff);
#endif


	int alpha = 255 * static_cast<float>(fadeFrame) / (float)kFadeFrame;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameoverScene::NormalDraw()
{
#ifdef _DEBUG
	DrawString(0, 0, "GameoverScene", 0xffffff);
#endif
}

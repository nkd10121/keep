#include "GamePlayingScene.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "StageSelect.h"
#include "PauseScene.h"
#include "../Game.h"
#include "../Player.h"
#include "../Input.h"
#include "../Enemy.h"
#include "../EnemyLine.h"

namespace
{
	constexpr int kEnemyLineMax = 32;
}

void GamePlayingScene::FadeInUpdate(Input& input)
{
	fadeFrame--;
	if (fadeFrame <= 0)
	{
		updateFunc_ = &GamePlayingScene::NormalUpdate;
		drawFunc_ = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input& input)
{
	//TODO:ステージクリアした時にステージセレクトに戻る
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
		drawFunc_ = &GamePlayingScene::FadeDraw;
	}
	//TODO:Escape or メニューボタンでPause画面に移動
	else if (input.IsTriggered("pause"))
	{
		manager_.PushScene(std::make_shared<PauseScene>(manager_));
	}
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	fadeFrame++;
	if (fadeFrame >= 60)
	{
		//TODO:ステージセレクト画面に遷移
		manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	//通常の描画
	//DrawString(100, 100, "GamePlayingScene", 0xffffff);

	int alpha = 255 * static_cast<float>(fadeFrame) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	//DrawString(100, 100, "GamePlayingScene", 0xffffff);
	//DrawFormatString(10, 10, 0xffffff, "fps=%2.2f", fps);
}


//-----------------------------------------------------------------//
GamePlayingScene::GamePlayingScene(SceneManager& mgr) :
	Scene(mgr),
	color(0),
	fps(0.0f),
	fadeFrame(0),
	enemyLineInterval(0)
{
	//メモリ確保
	player = new Player;
	enemy = new Enemy;

	eneLin.resize(kEnemyLineMax);

	for (int i = 0; i < kEnemyLineMax; i++)
	{
		eneLin[i] = nullptr;
	}

	player->Init();
	enemy->Init();

	color = (0xffffff);

	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	fadeFrame = 60;
}

GamePlayingScene::~GamePlayingScene()
{
	delete player;
	player = nullptr;

	delete enemy;
	enemy = nullptr;

	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i] != nullptr)
		{
			eneLin[i] = nullptr;
		}
	}
}

void GamePlayingScene::Update(Input& input)
{
	player->Update(input);
	enemy->Update();


	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			eneLin[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!eneLin[i]->isExist())
			{
				//メモリを解放する
				delete eneLin[i];
				eneLin[i] = nullptr;	//使っていないとわかるように
			}

		}
	}

	Rect playerRect = player->GetColRect();
	Rect enemyRect = enemy->GetColRect();

	if (playerRect.IsCollision(enemyRect))
	{
		//Debag用
#ifdef _DEBUG
		//printfDx("hit\n");
		color = (0xff0000);
#endif
		//playerをノックバックさせて少しの無敵時間を与える
		//ノックバック->playerにノックバックスピードを渡す関数を用意して
		//	player内でノックバックスピードを0にする処理を書く
		player->HitEnemy();

		//無敵時間 -> boolを返す関数を用意して
		//	player内でtrueの時点滅と当たり判定の削除を行う処理をする
	}
	else
	{
#ifdef _DEBUG
		color = (0xffffff);
#endif
	}

	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			Rect enemyLineRect = eneLin[i]->GetColRect();
			if (playerRect.IsCollision(enemyLineRect))
			{
				//Debag用
#ifdef _DEBUG
		//printfDx("hit\n");
				color = (0xff0000);
#endif
				//playerをノックバックさせて少しの無敵時間を与える
				//ノックバック->playerにノックバックスピードを渡す関数を用意して
				//	player内でノックバックスピードを0にする処理を書く
				player->HitEnemy();

				//無敵時間 -> boolを返す関数を用意して
				//	player内でtrueの時点滅と当たり判定の削除を行う処理をする
			}
			else
			{
#ifdef _DEBUG
				color = (0xffffff);
#endif
			}

		}
	}


	enemyLineInterval++;
	if (enemyLineInterval >= 30)
	{
		enemyLineInterval = 0;
		CreateEnemyLine();
	}

	enemy->SetColor(color);


	fps = GetFPS();
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	//背景
	DrawBox(0, 0, 1280, 720, 0x000000, true);

	enemy->Draw();
	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			eneLin[i]->Draw();

		}
	}

	player->Draw();

	(this->*drawFunc_)();
}

void GamePlayingScene::CreateEnemyLine()
{
	for (int i = 0; i < kEnemyLineMax; i++)
	{
		if (!eneLin[i])
		{
			eneLin[i] = new EnemyLine;
			eneLin[i]->Start();
			return;
		}
	}
}

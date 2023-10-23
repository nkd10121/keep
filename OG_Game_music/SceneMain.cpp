#include "SceneMain.h"
#include "Player.h"
#include "Rect.h"
#include "Enemy.h"
#include "DxLib.h"

SceneMain::SceneMain()
{
	//�������m��
	player = new Player;
	enemy = new Enemy;
}

SceneMain::~SceneMain()
{
	//���������
	delete player;
	player = nullptr;
	delete enemy;
	enemy = nullptr;
}

void SceneMain::Init()
{
	player->Init();
	enemy->Init();
}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	player->Update();
	enemy->Update();

	Rect playerRect = player->GetColRect();
	Rect enemyRect = enemy->GetColRect();

	if (playerRect.IsCollision(enemyRect))
	{
		printfDx("hit\n");
	}
}

void SceneMain::Draw()
{
	//�w�i
	DrawBox(0, 0, 640, 640, GetColor(16, 4, 16), true);

	player->Draw();
	enemy->Draw();
}

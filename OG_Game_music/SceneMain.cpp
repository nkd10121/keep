#include "SceneMain.h"
#include "Player.h"
#include "Rect.h"
#include "Enemy.h"
#include "DxLib.h"

SceneMain::SceneMain()
{
	//ƒƒ‚ƒŠŠm•Û
	player = new Player;
	enemy = new Enemy;

	color = (0xffffff);
}

SceneMain::~SceneMain()
{
	//ƒƒ‚ƒŠ‰ð•ú
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
#ifdef _DEBUG
		//printfDx("hit\n");
		color = (0xff0000);
#endif
	}
	else
	{
#ifdef _DEBUG
		color = (0xffffff);
#endif
	}

	enemy->SetColor(color);

}

void SceneMain::Draw()
{
	//”wŒi
	DrawBox(0, 0, 640, 640, GetColor(16, 4, 16), true);

	player->Draw();
	enemy->Draw();
}

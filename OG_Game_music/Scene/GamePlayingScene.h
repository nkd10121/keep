#pragma once
#include "Scene.h"
#include "../Vec2.h"

class Player;
class Enemy;

class GamePlayingScene : public Scene
{
public:
	GamePlayingScene(SceneManager& mgr);
	~GamePlayingScene();
	void Update(Input& input);
	void Draw();

private:

	Player* player;
	Enemy* enemy;

	unsigned int color;

	float fps = 0.0f;
	int frame_ = 0;

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (GamePlayingScene::*)(Input&);
	using DrawFunc_t = void (GamePlayingScene::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//�X�V�֐�
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//�`��֐�
	void FadeDraw();
	void NormalDraw();

};
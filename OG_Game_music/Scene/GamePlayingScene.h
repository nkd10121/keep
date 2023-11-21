#pragma once
#include <vector>

#include "Scene.h"
#include "../Vec2.h"

class Player;
class Enemy;
class EnemyLine;

class GamePlayingScene : public Scene
{
public:
	GamePlayingScene(SceneManager& mgr);
	~GamePlayingScene();
	void Update(Input& input);
	void Draw();

	void CreateEnemyLine();

private:

	Player* player;
	Enemy* enemy;

	//EnemyLine* eneLin;
	std::vector<EnemyLine*> eneLin;

	unsigned int color;

	float fps;
	int fadeFrame;

	int enemyLineInterval;

	int frame;
	int checkPointCount;
	int checkPointX;
	bool isDrawCheckPointLine;


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
#pragma once
#include "Scene.h"
#include "../Util/Col.h"
#include "../Util/Vec2.h"
#include <vector>
#include <string>

class Player;
class TargetCircle;
class DrawBGparts;

enum NextScene
{
	No,
	nTutorial,
	nStage1,
	nStage2
};

class StageSelect : public Scene
{
private:
	int frame_ = 0;

	NextScene next = No;
	NextScene nextLog = No;

	//�w�i�̎l�p
	std::vector<DrawBGparts*> parts;
	//�w�i��U��������{��
	float mag = 1.0f;
	//�w�i�̎l�p�̉�]���x
	float rotateSpeed = 0;

	Player* player;
	Col playerCol;
	std::vector<TargetCircle*> target;

	int soundFadeFrame = 0;
	bool isSoundFade = false;

	int expandFrame = 0;

	void SetNextInfo(int kindNum);

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (StageSelect::*)(Input&);
	using DrawFunc_t = void (StageSelect::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//�X�V�֐�
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//�`��֐�
	void FadeDraw();
	void NormalDraw();

public:
	StageSelect(SceneManager& mgr);
	~StageSelect();
	void Update(Input& input);
	void Draw();

	void CreateTargetCircle(int x,int y,int handleNum);
};


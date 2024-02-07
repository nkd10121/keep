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

	//”wŒi‚ÌlŠp
	std::vector<DrawBGparts*> parts;
	//”wŒi‚ğU“®‚³‚¹‚é”{—¦
	float mag = 1.0f;
	//”wŒi‚ÌlŠp‚Ì‰ñ“]‘¬“x
	float rotateSpeed = 0;

	Player* player;
	Col playerCol;
	std::vector<TargetCircle*> target;

	int soundFadeFrame = 0;
	bool isSoundFade = false;

	int expandFrame = 0;

	void SetNextInfo(int kindNum);

	//ó‘Ô‘JˆÚ—pƒƒ“ƒoŠÖ”ƒ|ƒCƒ“ƒ^‚ÌéŒ¾
	using UpdateFunc_t = void (StageSelect::*)(Input&);
	using DrawFunc_t = void (StageSelect::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//XVŠÖ”
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//•`‰æŠÖ”
	void FadeDraw();
	void NormalDraw();

public:
	StageSelect(SceneManager& mgr);
	~StageSelect();
	void Update(Input& input);
	void Draw();

	void CreateTargetCircle(int x,int y,int handleNum);
};


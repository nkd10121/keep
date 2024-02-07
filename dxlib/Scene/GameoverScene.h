#pragma once
#include "Scene.h"
#include "../Util/Vec2.h"

#include <vector>

enum Button
{
	Retry,
	Return
};

class DrawBGparts;
class Efects;
class AfterImagePlayer;

class GameoverScene : public Scene
{
public:
	GameoverScene(SceneManager& mgr);
	~GameoverScene();
	void Update(Input& input);
	void Draw();

private:
	int fadeFrame = 0;
	int m_frame = 0;

	int nowButton = Retry;

	int retryButtonX;
	int returnButtonX;

	int handle[4];

	Vec2 m_playerPos;
	Vec2 offset{};

	std::vector<DrawBGparts*> parts;

	bool isRevival;
	bool deathAnimationFlag;

	std::vector<AfterImagePlayer*> afterImage;
	std::vector<Efects*> efects;

	void CreateAfterImage(Vec2 pos);

	void CreateDashEfect(Vec2 pos, bool isLastHit = false);

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (GameoverScene::*)(Input&);
	using DrawFunc_t = void (GameoverScene::*)();

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


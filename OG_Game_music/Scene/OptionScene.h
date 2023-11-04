#pragma once
#include "Scene.h"
class OptionScene :
    public Scene
{
private:
	int frame_ = 0;

	int cursolPosX;
	int cursolPosY;

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (OptionScene::*)(Input&);
	using DrawFunc_t = void (OptionScene::*)();

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
	OptionScene(SceneManager& mgr);
	~OptionScene();
	void Update(Input& input);
	void Draw();
};


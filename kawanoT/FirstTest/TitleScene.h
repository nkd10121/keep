#pragma once
#include "Scene.h"

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{
private:
	int handle_ = 0;
	int frame_ = 0;
	//�X�V�����o�֐��|�C���^
	void (TitleScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void (TitleScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void FadeInUpdate(Input&);	//�t�F�[�h�C�����
	void NormalUpdate(Input& input);	//�ʏ���
	void FadeOutUpdate(Input&);	//�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();
	void NormalDraw();

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Update(Input& input);
	void Draw();
};


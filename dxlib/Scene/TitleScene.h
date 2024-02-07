#pragma once
#include "Scene.h"
#include "DxLib.h"

#include <vector>
/// <summary>
/// �I�����Ă���{�^��
/// </summary>
enum ButtonName
{
	Play,
	Option,
	Quit
};

class DrawBGparts;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{
private:
	//�I�����Ă���{�^��
	int nowButton = Play;

	int m_fadeFrame = 0;
	int frame = 3;

	//�w�i��U��������{��
	float mag = 1.0f;
	//�^�C�g�����S�̃T�C�Y
	float titleSize = 0.28f;
	//�^�C�g����Y���W
	int titlePosY = 280;

	//�v���C�{�^����X���W
	int playButtonPosX;
	//�I�v�V�����{�^����X���W
	int optionButtonPosX;
	//��߂�{�^����X���W
	int quitButtonPosX;

	std::vector<DrawBGparts*> parts;

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
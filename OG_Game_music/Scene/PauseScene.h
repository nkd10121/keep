#pragma once
#include "Scene.h"

class Input;
class SceneManager;

class PauseScene :public Scene
{
private:
	int frame_ = 0;
	//�X�V�����o�֐��|�C���^
	using UpdateFunc_f = void (PauseScene::*)(Input& input);
	UpdateFunc_f updateFunc_;

	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void (PauseScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void AppearUpdate(Input&);		//�o����
	void NormalUpdate(Input&);		//�ʏ���
	void DisappearUpdate(Input&);	//�ޏ���

	//�`��֐�
	void ExpandDraw();		//�g���k���`��
	void NormalDraw();	//�ʏ�`��

public:
	PauseScene(SceneManager& manager);
	void Update(Input& input);
	void Draw();
};
#pragma once
#pragma once
#include "Scene.h"
#include "../Util/Vec2.h"

#include <vector>

/// <summary>
/// ���̍���
/// </summary>
enum Item
{
	Setting,
	Operation,
	ToTitle,
	Close,
	BGM,
	SE,
	FullScreen,
	ReturnTitle

};

struct Info
{
	Item item;
	Vec2 pos;
};

class AfterImagePlayer;

class PauseScene :public Scene
{
public:
	PauseScene(SceneManager& manager);
	~PauseScene();
	void Update(Input& input);
	void Draw();

private:
	int m_frame = 0;

	int pHandle = -1;
	int checkHandle = -1;

	//�v���C���[�̊p�x
	float angle = 0;

	int BGMnum = 5;
	int SEnum = 5;
	bool isFullScreen = false;

	bool isFromToTitle = false;
	bool isReturn = false;

	//�J�[�\���̏��
	Info cursol;
	Info cursolLog;

	//���ڂ̑I�����̏��
	Info test[8];

	//�c��
	std::vector<AfterImagePlayer*> afterImage;
	//�c�������̊֐�
	void CreateAfterImage(Vec2 pos);

	//�X�V�����o�֐��|�C���^
	void (PauseScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	void (PauseScene::* drawFunc_)();

	//�ʏ��Ԃ�Update
	void DefaultUpdate(Input& input);
	//�ݒ��Ԃ�Update
	void SettingUpdate(Input& input);

	void ReturnTitleUpdate(Input& input);

	//�ݒ��Ԃ�Draw
	void SettingDraw();
	//���������Ԃ�Draw
	void OperationDraw();

	void ReturnTitleDraw();
	//�����Ԃ�Draw
	void CloseDraw();
};
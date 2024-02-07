#pragma once
#include "Scene.h"
#include "../Util/Vec2.h"

#include <vector>

/// <summary>
/// ���̍���
/// </summary>
enum Item
{
	//�ݒ�
	Setting,
	//�������
	Operation,
	//�����\�L
	Credit,
	//����
	Close,
	//BGM
	BGM,
	//SE
	SE,
	//�t���X�N���[��
	FullScreen
};

/// <summary>
/// ���ږ��ƍ��W������
/// </summary>
struct Info
{
	//���ږ�
	Item item;
	//���W
	Vec2 pos;
};

class AfterImagePlayer;

class OptionScene :  public Scene
{
public:
	OptionScene(SceneManager& manager);
	~OptionScene();
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

	//�J�[�\���̏��
	Info cursol;
	Info cursolLog;

	//���ڂ̑I�����̏��
	Info test[7];

	//�c��
	std::vector<AfterImagePlayer*> afterImage;
	//�c�������̊֐�
	void CreateAfterImage(Vec2 pos);

	//�X�V�����o�֐��|�C���^
	void (OptionScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	void (OptionScene::* drawFunc_)();

	//�ʏ��Ԃ�Update
	void DefaultUpdate(Input& input);
	//�ݒ��Ԃ�Update
	void SettingUpdate(Input& input);

	//�ݒ��Ԃ�Draw
	void SettingDraw();
	//���������Ԃ�Draw
	void OperationDraw();
	//�����\�L��Ԃ�Draw
	void CreditDraw();
	//�����Ԃ�Draw
	void CloseDraw();
};


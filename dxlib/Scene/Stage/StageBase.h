#pragma once
#include <vector>

#include "DxLib.h"
#include "../Scene.h"
#include "../../Util/Vec2.h"
#include "../../Util/Col.h"
#include "../../Util/Game.h"

class Player;
class GoalEfect;
class EnemyLineBase;
class EnemyCircleBase;
class Goal;

class StageBase : public Scene
{
public:
	StageBase(SceneManager& mgr);
	~StageBase();
	virtual void Update(Input& input);
	virtual void Draw();

	/// <summary>
	/// ���C���n�̓G�̍쐬�֐�
	/// </summary>
	/// <param name="pos">�E��̍��W</param>
	/// <param name="width">�傫��</param>
	/// <param name="first">�{�̂������t���[��</param>
	/// <param name="second">�{�̂������n�߂�t���[��</param>
	/// <param name="enemy">Line�̎��</param>
	void CreateEnemyLineFrom(Vec2 pos, int width,int first,int second, EnemyLineBase* enemy);

	/// <summary>
	/// Box�G�̍쐬�֐�
	/// </summary>
	/// <param name="pos">���S���W</param>
	/// <param name="size">��ӂ̒���</param>
	/// <param name="speed">�傫���Ȃ鑬��</param>
	/// <param name="firstFrame">�{�̂��o�Ă���t���[��</param>
	/// <param name="secondFrame">�{�̂������n�߂�t���[��</param>
	/// <param name="isPre">�\����������邩�ǂ���</param>
	void CreateEnemyBox(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre = true);

	void CreateEnemyCircle(float pos, int radius, bool isSmooth);

	void CreateEnemyBurst(Vec2 pos, Vec2 vec, int speed, int first, int second);

	void CreateEnemyCircleScaling(Vec2 pos, int rad,int first,int second,int speed = 20);

	void AddEnemy(EnemyLineBase* test);


protected:
	//Update�̍ŏ��̃t���[���̏����̂��߂�bool
	bool isFirst = true;

	/*�v���C���[�֘A*/
	//�v���C���[�{��
	Player* player;
	//�v���C���[�̓����蔻��
	Col playerCol;

	/*��`�̓����蔻������G�֌W*/
	std::vector<EnemyLineBase*> eneLine;
	Vec2 eneLinePos;
	int lineWidth;

	/*�~�̓����蔻������G�֌W*/
	std::vector<EnemyCircleBase*> eneCircle;
	Vec2 eneCirclePos;
	Vec2 eneCircleBurstVec;
	int eneCircleRadius;
	int eneCircleBurstSpeed;

	int frame;

	Goal* goal;
	bool goalFlag = false;
	bool onGoal = false;

	//��̃Q�[�W�̂��
	float progressSpeed = 0.0f;

	float progressPos = 520.0f;

	/*��ʗh�炷�֌W*/
	int screenX = 0;
	int screenY = 0;
	int m_shakeFrame = 0;
	int m_gameScreenHandle = 0;
	float m_amp = 0;

	//�S�[���G�t�F�N�g
	bool isStartGoalEfect = false;
	int goalEfectFrame = 0;
	GoalEfect* goalEfect;

	//�T�E���h�̃t�F�[�h�A�E�g
	bool isSoundFadeOut = false;
	int soundFadeFrame = 0;

	//��ʓ_�ł�bool
	bool m_isHitFlash = false;
	int alpha = 0;

	float GetRandF(int num) { return (float)GetRand(num); }

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (StageBase::*)(Input&);
	using DrawFunc_t = void (StageBase::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	int fadeFrame;

	//�v���C���[���G�ɓ����������̏������܂Ƃ߂��֐�
	void PlayerHit();

	//�X�V�֐�
	virtual void FadeInUpdate(Input& input);
	virtual void NormalUpdate(Input& input);
	virtual void FadeOutUpdate(Input& input);

	//�`��֐�
	void FadeDraw();
	void NormalDraw();
};


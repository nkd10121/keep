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
	/// ライン系の敵の作成関数
	/// </summary>
	/// <param name="pos">右上の座標</param>
	/// <param name="width">大きさ</param>
	/// <param name="first">本体が動くフレーム</param>
	/// <param name="second">本体が消え始めるフレーム</param>
	/// <param name="enemy">Lineの種類</param>
	void CreateEnemyLineFrom(Vec2 pos, int width,int first,int second, EnemyLineBase* enemy);

	/// <summary>
	/// Box敵の作成関数
	/// </summary>
	/// <param name="pos">中心座標</param>
	/// <param name="size">一辺の長さ</param>
	/// <param name="speed">大きくなる速さ</param>
	/// <param name="firstFrame">本体が出てくるフレーム</param>
	/// <param name="secondFrame">本体が消え始めるフレーム</param>
	/// <param name="isPre">予備動作をするかどうか</param>
	void CreateEnemyBox(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre = true);

	void CreateEnemyCircle(float pos, int radius, bool isSmooth);

	void CreateEnemyBurst(Vec2 pos, Vec2 vec, int speed, int first, int second);

	void CreateEnemyCircleScaling(Vec2 pos, int rad,int first,int second,int speed = 20);

	void AddEnemy(EnemyLineBase* test);


protected:
	//Updateの最初のフレームの処理のためのbool
	bool isFirst = true;

	/*プレイヤー関連*/
	//プレイヤー本体
	Player* player;
	//プレイヤーの当たり判定
	Col playerCol;

	/*矩形の当たり判定を持つ敵関係*/
	std::vector<EnemyLineBase*> eneLine;
	Vec2 eneLinePos;
	int lineWidth;

	/*円の当たり判定を持つ敵関係*/
	std::vector<EnemyCircleBase*> eneCircle;
	Vec2 eneCirclePos;
	Vec2 eneCircleBurstVec;
	int eneCircleRadius;
	int eneCircleBurstSpeed;

	int frame;

	Goal* goal;
	bool goalFlag = false;
	bool onGoal = false;

	//上のゲージのやつ
	float progressSpeed = 0.0f;

	float progressPos = 520.0f;

	/*画面揺らす関係*/
	int screenX = 0;
	int screenY = 0;
	int m_shakeFrame = 0;
	int m_gameScreenHandle = 0;
	float m_amp = 0;

	//ゴールエフェクト
	bool isStartGoalEfect = false;
	int goalEfectFrame = 0;
	GoalEfect* goalEfect;

	//サウンドのフェードアウト
	bool isSoundFadeOut = false;
	int soundFadeFrame = 0;

	//画面点滅のbool
	bool m_isHitFlash = false;
	int alpha = 0;

	float GetRandF(int num) { return (float)GetRand(num); }

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (StageBase::*)(Input&);
	using DrawFunc_t = void (StageBase::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	int fadeFrame;

	//プレイヤーが敵に当たった時の処理をまとめた関数
	void PlayerHit();

	//更新関数
	virtual void FadeInUpdate(Input& input);
	virtual void NormalUpdate(Input& input);
	virtual void FadeOutUpdate(Input& input);

	//描画関数
	void FadeDraw();
	void NormalDraw();
};


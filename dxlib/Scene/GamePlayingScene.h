//#pragma once
//#include <vector>
//
//#include "Scene.h"
//#include "DxLib.h"
//#include "../Util/Vec2.h"
//
//class Player;
//class EnemyLineBase;
//class EnemyCircleBase;
//class Goal;
//
//class GamePlayingScene : public Scene
//{
//public:
//	GamePlayingScene(SceneManager& mgr);
//	~GamePlayingScene();
//	void Update(Input& input);
//	void Draw();
//
//	void CreateEnemyLineFrom(Vec2 pos, int width,int first,int second, EnemyLineBase* enemy);
//
//	void CreateEnemyCircle(float pos, int radius, bool isSmooth);
//
//	void CreateEnemyBurst(Vec2 pos, Vec2 vec, int speed);
//
//	void CreateEnemyCircleScaling(Vec2 pos, int rad);
//
//	void AddEnemy(EnemyLineBase* test);
//
//	float GetRandF(int num) { return (float)GetRand(num); }
//private:
//	int enemyIntervalFrame;
//
//	float startTime;
//	float nowTime;
//
//	Player* player;
//
//	std::vector<EnemyLineBase*> eneLine;
//	Vec2 eneLinePos;
//	int lineWidth;
//
//	std::vector<EnemyCircleBase*> eneCircle;
//	Vec2 eneCirclePos;
//	Vec2 eneCircleBurstVec;
//	int eneCircleRadius;
//	int eneCircleBurstSpeed;
//
//	int fadeFrame;
//
//	int enemyGenerateFrame;
//
//	int frame;
//	int checkPointCount;
//	int checkPointX;
//	bool isDrawCheckPointLine;
//
//	Goal* goal;
//	bool onGoal;
//
//	//状態遷移用メンバ関数ポインタの宣言
//	using UpdateFunc_t = void (GamePlayingScene::*)(Input&);
//	using DrawFunc_t = void (GamePlayingScene::*)();
//
//	UpdateFunc_t updateFunc_ = nullptr;
//	DrawFunc_t drawFunc_ = nullptr;
//
//	//更新関数
//	void FadeInUpdate(Input& input);
//	void NormalUpdate(Input& input);
//	void FadeOutUpdate(Input& input);
//
//	//描画関数
//	void FadeDraw();
//	void NormalDraw();
//
//};
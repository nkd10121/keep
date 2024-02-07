#pragma once
#include "EnemyCircleBase.h"
#include "EnemyBurstedCircle.h"
#include "../../Util/Col.h"
#include <vector>
#include <memory>

//MEMO:もしstageBase的なステージの根元の作るならここを変更する必要があるかも

//class GamePlayingScene;
class StageBase;

class EnemyBurst :
    public EnemyCircleBase
{
public:
    //EnemyBurst(GamePlayingScene* scene);
    EnemyBurst(StageBase* scene);
    ~EnemyBurst();

    void Start(Vec2 pos, Vec2 vec,int speed,int first,int second)override;
    void Update()override;
    void Draw()override;

    void CreateBurstedCircle(Vec2 pos, Vec2 vec);


private:
    //GamePlayingScene* test;
    StageBase* stage;

    //フレーム数
    int frame;

    int m_firstFrame;
    int m_secondFrame;

    //差分
    Vec2 offset;
    //角度
    float angle;
    //最初の大きい円の半径
    int radius;

    float m_speed;

    float diagonal;
    //目的の座標
    Vec2 m_vec;

    bool isBurst;
    Vec2 circlePos;

    //std::vector<EnemyBurstedCircle*> burstedCircle;
    std::vector<EnemyCircleBase*> burstedCircle;
};
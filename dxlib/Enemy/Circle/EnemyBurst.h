#pragma once
#include "EnemyCircleBase.h"
#include "EnemyBurstedCircle.h"
#include "../../Util/Col.h"
#include <vector>
#include <memory>

//MEMO:����stageBase�I�ȃX�e�[�W�̍����̍��Ȃ炱����ύX����K�v�����邩��

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

    //�t���[����
    int frame;

    int m_firstFrame;
    int m_secondFrame;

    //����
    Vec2 offset;
    //�p�x
    float angle;
    //�ŏ��̑傫���~�̔��a
    int radius;

    float m_speed;

    float diagonal;
    //�ړI�̍��W
    Vec2 m_vec;

    bool isBurst;
    Vec2 circlePos;

    //std::vector<EnemyBurstedCircle*> burstedCircle;
    std::vector<EnemyCircleBase*> burstedCircle;
};
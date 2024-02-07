#include "EnemyBurst.h"
//#include "../../Scene/GamePlayingScene.h"
#include "../../Scene/Stage/StageBase.h"

namespace
{
	constexpr int kBurstedCircleNum = 8;

	const Vec2 kUp = { 0.0f,1.0f };
	const Vec2 kRight = { 1.0f,0.0f };
	const Vec2 kDown = { 0.0f,-1.0f };
	const Vec2 kLeft = { -1.0f,0.0f };
}

//EnemyBurst::EnemyBurst(GamePlayingScene* scene):
EnemyBurst::EnemyBurst(StageBase* scene):
	stage(scene),
	frame(0),
	m_firstFrame(0),
	m_secondFrame(0),
	offset(0,0),
	angle(0),
	radius(0),
	m_speed(0.0f),
	diagonal(0),
	m_vec((float)GetRand(1280) - 640,(float)GetRand(960) - 480),
	isBurst(false),
	circlePos(0,0)
{
	burstedCircle.resize(kBurstedCircleNum);

}

EnemyBurst::~EnemyBurst()
{
}

void EnemyBurst::Start(Vec2 pos, Vec2 vec, int speed, int first, int second)
{
	m_pos = pos;
	m_vec = vec;
	m_speed = static_cast<float>(speed);

	m_firstFrame = first;
	m_secondFrame = second;

	m_isExist = true;
	
}

void EnemyBurst::Update()
{
	frame++;

	angle += 0.14f;

	//DrawBox(X, Y  , X + width, Y + height, 0xffffff, true);

	if (frame % 4 == 0 && frame > m_secondFrame - 24)
	{
		m_color = 0xffffff;
	}
	else
	{
		m_color = 0xff00ff;
	}

	if (frame <= m_firstFrame)
	{
		radius += 2;
		diagonal = static_cast<float>(radius) + (static_cast<float>(radius) / 4);
	}

	if (frame <= m_secondFrame)
	{
		m_pos += m_vec.getNormalize() * m_speed;

		m_col.SetCircle(m_pos.x,m_pos.y, radius);

		offset.x = cosf(angle + 0.75f) * diagonal;
		offset.y = sinf(angle + 0.75f) * diagonal;
	}
	else if (!isBurst)
	{
		isBurst = true;

		circlePos = m_pos;
		m_pos = { -1000,-1000 };

		CreateBurstedCircle(circlePos, kUp);
		CreateBurstedCircle(circlePos, kUp + kRight);
		CreateBurstedCircle(circlePos, kRight);
		CreateBurstedCircle(circlePos, kRight + kDown);
		CreateBurstedCircle(circlePos, kDown);
		CreateBurstedCircle(circlePos, kDown + kLeft);
		CreateBurstedCircle(circlePos, kLeft);
		CreateBurstedCircle(circlePos, kLeft + kUp);
	}

	m_speed -= 0.8f;
	//ちょっとずつスピードを下げる
	if (m_speed < 0)
	{
		m_speed = 0.0f;
	}

	if (frame >= m_secondFrame + 30)
	{
		m_isExist = false;
	}

	//m_colRect.SetCircle(m_pos, radius);
	m_col.SetCircle(m_pos.x, m_pos.y, radius);
}

void EnemyBurst::Draw()
{
	if (frame <= m_secondFrame)
	{
		DrawQuadrangle(
			static_cast<int>(m_pos.x - offset.x), static_cast<int>(m_pos.y - offset.y),
			static_cast<int>(m_pos.x + offset.y), static_cast<int>(m_pos.y - offset.x),
			static_cast<int>(m_pos.x + offset.x), static_cast<int>(m_pos.y + offset.y),
			static_cast<int>(m_pos.x - offset.y), static_cast<int>(m_pos.y + offset.x),
			m_color,
			true
		);
	

		DrawCircle(static_cast<int>(m_pos.x) - 1, static_cast<int>(m_pos.y) - 1, radius, m_color, true);

#ifdef _DEBUG
		//m_colRect.DrawRectCircle(0xffffff, false);
		m_col.DrawColCircle(0xffffff);
#endif
	}
}

void EnemyBurst::CreateBurstedCircle(Vec2 pos, Vec2 vec)
{
	//ここで作るだけ作ってUpdateやDrawはGamePlayingSceneに渡してしまう
	EnemyBurstedCircle* enemy = new EnemyBurstedCircle;
	enemy->Start(pos, vec);
	stage->AddEnemy(enemy);
}

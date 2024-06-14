#include "SceneBase.h"
#include "DxLib.h"
#include "game.h"
#include "Mouse.h"

#include <cassert>
#include "Player.h"
#include "Sound.h"

namespace
{
	// �t�F�[�h�ɂ�����t���[���f�t�H���g
	constexpr int kFadeFrameDefault = 32;
//	constexpr int kFadeFrameDefault = 60 * 5;

	// �}�E�X�J�[�\���T�C�Y
	constexpr int kCursorSize = 32;

	// �t�F�[�h�J���[
	constexpr unsigned int kFadeColor[] =
	{
		// ������ƈÂ�
		0xe06060,
		0xe060a0,
		0xe060e0,
		0xa060e0,
		0x6060e0,
		0x60a0e0,
		0x60e0e0,
		0x60e0a0,
		0x60e060,
		0xa0e060,
		0xe0e060,
		0xe0a060
	};
	constexpr int kFadeColorNum = _countof(kFadeColor);


	// �������̃O���f�[�V�����̎l�p�`��`�悷��
	void GradX_RGB(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
	{
		VERTEX2D Vertex[6];

		// ����̒��_�̏����Z�b�g( 1�|���S���ڂ̑�1���_ )
		Vertex[0].pos.x = (float)x1;
		Vertex[0].pos.y = (float)y1;
		Vertex[0].pos.z = 0.0f;
		Vertex[0].rhw = 1.0f;
		Vertex[0].dif.r = r1;
		Vertex[0].dif.g = g1;
		Vertex[0].dif.b = b1;
		Vertex[0].dif.a = 255;
		Vertex[0].u = 0.0f;
		Vertex[0].v = 0.0f;

		// �E��̒��_�̏����Z�b�g( 1�|���S���ڂ̑�2���_ )
		Vertex[1].pos.x = (float)x2;
		Vertex[1].pos.y = (float)y1;
		Vertex[1].pos.z = 0.0f;
		Vertex[1].rhw = 1.0f;
		Vertex[1].dif.r = r1;
		Vertex[1].dif.g = g1;
		Vertex[1].dif.b = b1;
		Vertex[1].dif.a = 255;
		Vertex[1].u = 0.0f;
		Vertex[1].v = 0.0f;

		// �����̒��_�̏����Z�b�g( 1�|���S���ڂ̑�3���_ )
		Vertex[2].pos.x = (float)x1;
		Vertex[2].pos.y = (float)y2;
		Vertex[2].pos.z = 0.0f;
		Vertex[2].rhw = 1.0f;
		Vertex[2].dif.r = r2;
		Vertex[2].dif.g = g2;
		Vertex[2].dif.b = b2;
		Vertex[2].dif.a = 255;
		Vertex[2].u = 0.0f;
		Vertex[2].v = 0.0f;

		// �E���̒��_�̏����Z�b�g( 2�|���S���ڂ̑�1���_ )
		Vertex[3].pos.x = (float)x2;
		Vertex[3].pos.y = (float)y2;
		Vertex[3].pos.z = 0.0f;
		Vertex[3].rhw = 1.0f;
		Vertex[3].dif.r = r2;
		Vertex[3].dif.g = g2;
		Vertex[3].dif.b = b2;
		Vertex[3].dif.a = 255;
		Vertex[3].u = 0.0f;
		Vertex[3].v = 0.0f;

		// 2�|���S���ڂ̑�2���_�͍����̒��_�Ȃ̂ŃR�s�[
		Vertex[4] = Vertex[2];

		// 2�|���S���ڂ̑�3���_�͉E��̒��_�Ȃ̂ŃR�s�[
		Vertex[5] = Vertex[1];

		// �|���S����2�`��
		DrawPolygon2D(Vertex, 2, DX_NONE_GRAPH, FALSE);
	}
}

SceneBase::SceneBase() :
	m_fadeMask(-1),
	m_isInit(false),
	m_fadeFrame(kFadeFrameDefault),
	m_fadeTotalFrame(kFadeFrameDefault),
	m_fadeDir(0),
	m_fadeColor(0x000000),
	m_fadePlayerKind(0),
	m_isDispLoading(false),
	m_loadFrame(0),
	m_isDispCursor(true),
	m_isEnd(false),
	m_pNext(nullptr)
#ifdef DISP_PROCESS
	,m_updateTime(0),
	m_drawTime(0)
#endif
{
}

void SceneBase::setNextScene(SceneBase* pNext)
{
//	assert(!isFading());
	assert(!m_isEnd);

	m_isEnd = true;
	m_pNext = pNext;

	startFadeOut();
	// �J�ڌ��Ɠ����J���[�Ńt�F�[�h����悤�ɐݒ肷��
	if (m_pNext)
	{
		m_pNext->setFadeColor(getFadeColor());
		m_pNext->setFadePlayerKind(getFadePlayerKind());
	}
}

float SceneBase::getFadeProgress() const
{
	return static_cast<float>(m_fadeFrame) / static_cast<float>(m_fadeTotalFrame);
}

void SceneBase::initAll()
{
	// �t�F�[�h�A�E�g��Ԃ���J�n
	m_fadeFrame = m_fadeTotalFrame;
	startFadeIn();
	// �p����V�[���̏���������
	init();

	// �}�X�N�����̏���
	CreateMaskScreen();

	m_fadeMask = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	SetMaskScreenGraph(m_fadeMask);
}

void SceneBase::endAll()
{
	// �p����V�[���̏I������
	end();

	DeleteMask(m_fadeMask);	// TODO�I����������ł����Ă��邩������
	DeleteGraph(m_fadeMask);

	DeleteMaskScreen();
}

void SceneBase::updateAll()
{
#ifdef DISP_PROCESS
	LONGLONG start = GetNowHiPerformanceCount();
#endif
	if (!isLoaded())
	{
		// ���\�[�X�̃��[�h�ɂ������Ă���t���[�������J�E���g
		m_loadFrame++;
	//	printfDx("LoadFrame : %d\n", m_loadFrame);
		return;	// ���[�h���͍X�V���������s��Ȃ�
	}
	if (!m_isInit)
	{
		initAll();
		m_isInit = true;
	}

	updateFade();
	// �p����V�[���̍X�V����
	update();
#ifdef DISP_PROCESS
	m_updateTime = GetNowHiPerformanceCount() - start;
#endif
}

void SceneBase::drawAll()
{
#ifdef DISP_PROCESS
	LONGLONG start = GetNowHiPerformanceCount();
#endif
	// �p����V�[���̕`�揈��
	draw();
//	drawCursor();
	drawFade();
	drawLoading();
	drawFront();
#ifdef _DEBUG
	drawDebug();
#endif

#ifdef DISP_PROCESS
	m_drawTime = GetNowHiPerformanceCount() - start;

	// �����o�[�̕\��
	// ���� 
	DrawString(0, Game::kScreenHeight - 48, "����", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 48 + 2, 48 + 16 - 2, Game::kScreenHeight - 32 - 2, 0x0000ff, true);
	DrawString(0, Game::kScreenHeight - 32, "�`��", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 32 + 2, 48 + 16 - 2, Game::kScreenHeight - 16 - 2, 0xff0000, true);

//	DrawBox(0,Game::kScreenHeight - 16, Game::kScreenWidth, Game::kScreenHeight,0xffffff, false);	// �O�g

	float rate = static_cast<float>(m_updateTime + m_drawTime) / 16666.6f;
	int width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0xff0000, true);	// ����+�`��
//	DrawFormatString(width, Game::kScreenHeight - 16, 0xffffff, "%d", m_updateTime + m_drawTime);

	rate = static_cast<float>(m_updateTime) / 16666.6f;
	width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0x0000ff, true);	// ����+�`��̏ォ�珈�����Ԃ̂ݕ`��
#endif
}

bool SceneBase::isSceneEnd()
{
	// ���������I���ƌ����Ă��Ȃ�
	if (!m_isEnd)	return false;
	// �܂��t�F�[�h�A�E�g�I����ĂȂ�
	if (m_fadeFrame < m_fadeTotalFrame)	return false;
	
	return true;
}

void SceneBase::updateFade()
{
	// ���\�[�X�̃��[�h���������Ă��Ȃ�
	if (m_fadeDir < 0 && (!isLoaded()))
	{
		return;	// ���[�h�����܂ł̓t�F�[�h�C���������s��Ȃ�
	}

	m_fadeFrame += m_fadeDir;
	if (m_fadeFrame >= m_fadeTotalFrame)
	{
		m_fadeFrame = m_fadeTotalFrame;
		m_fadeDir = 0;
	}
	if (m_fadeFrame <= 0)
	{
		m_fadeFrame = 0;
		m_fadeDir = 0;
	}
}

void SceneBase::drawFade() const
{
#if true
	// ���S�ɕ\������Ă����ԂȂ̂Ńt�F�[�h�͕\�����Ȃ�
	if (m_fadeFrame <= 0)	return;

	// �}�X�N�̐���
	SetDrawScreen(m_fadeMask);
	ClearDrawScreen();

	constexpr int kHalfWidth = Game::kScreenWidth / 2;
	constexpr int kHalfHeight = Game::kScreenHeight / 2;

	float rate = getFadeProgress() / 0.9f;	// 0.9�ȏ�Ȃ犮�S�ɉB�ꂽ��Ԃɂ���
//	float rate = getFadeProgress();
	rate = min(rate, 1.0f);
	rate *= rate;

	// �^�����Ńv���C���[��`�悷��
	SetDrawBright(0, 0, 0);
#if false
	double scale = 72.0 * (1.0f - rate);
	int animNo = (m_fadeFrame / 2) % Player::getRunAnimeNum();
	DrawRectRotaGraph(kHalfWidth, kHalfHeight, animNo * 32, 0, 32, 32, scale, 0.0, Player::getGraph(m_fadePlayerKind), true);
#else
	// ��ʂ𕪊����ăv���C���[����������\��
#if false
	constexpr int kSplitX = 16;
	constexpr int kSplitY = 9;
//	constexpr double kMaxScale = 72.0 / kSplitX;
	constexpr double kMaxScale = 6.0;
#else
	constexpr int kSplitX = 12;
	constexpr int kSplitY = 7;
	//	constexpr double kMaxScale = 72.0 / kSplitX;
	constexpr double kMaxScale = 8.0;
#endif
	constexpr int kSplitNum = kSplitX * kSplitY;
	constexpr int kIntervalX = Game::kScreenWidth / kSplitX;
	constexpr int kIntervalY = Game::kScreenHeight / kSplitY;
	constexpr int kStartX = kIntervalX / 2;
	constexpr int kStartY = kIntervalY / 2;

	for (int x = 0; x < kSplitX; x++)
	{
		

		for (int y = 0; y < kSplitY+1; y++)
		{
			// �X�P�[�����O�ɂ�����t���[������ς���
			int startFrame = (x+y) * 1;
			int endFrame = m_fadeTotalFrame - kSplitX + (x + y) * 1 - 1;
			if (m_fadeDir < 0)
			{
				startFrame = kSplitX - (x + y) * 1 - 1;
				endFrame = m_fadeTotalFrame - kSplitX + (kSplitX - (x + y) * 1 - 1) - 1;
			}

			const int kScaleFrameTotal = endFrame - startFrame;
			const int kCurrentFeame = m_fadeFrame - startFrame;

			double scaleRate = static_cast<double>(kCurrentFeame) / static_cast<double>(kScaleFrameTotal);
			scaleRate = max(0.0, scaleRate);

			if (scaleRate >= 1.0)	continue;

			double scale = kMaxScale * (1.0 - scaleRate);
			int animNo = (m_fadeFrame / 2) % Player::getRunAnimeNum();

			int posX = kStartX + kIntervalX * x;
			int posY = kStartY + kIntervalY * y - kIntervalY/2 * (x % 2);

			DrawRectRotaGraph(posX, posY, animNo * 32, 0, 32, 32, scale, 0.0, Player::getRunGraph(m_fadePlayerKind), true);
		}
	}
#endif

	// ���ɖ߂�
	SetDrawBright(255, 255, 255);

	// �t�F�[�h�ʂ̕`��
	SetDrawScreen(DX_SCREEN_BACK);

	// �}�X�N�t���̋�`�`��
	SetUseMaskScreenFlag(true);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
//	GradX_RGB(0, 0, Game::kScreenWidth, Game::kScreenHeight, (m_fadeColor >> 16) & 0xff, (m_fadeColor >> 8) & 0xff, (m_fadeColor >> 0) & 0xff, 255, 255, 255);

	// �}�X�N�ݒ�߂�
	SetUseMaskScreenFlag(false);
#else
	// ���S�ɕ\������Ă����ԂȂ̂Ńt�F�[�h�͕\�����Ȃ�
	if (m_fadeFrame <= 0)	return;

	float rate = getFadeProgress();
	int startX = 0;
	int endX = Game::kScreenWidth;

	if (m_fadeDir < 0)
	{
		// �t�F�[�h�C����
		endX = static_cast<int>(Game::kScreenWidth * rate);
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int elem = GetRand(16) + 4;
			DrawLine(startX, y, endX - GetRand(128), y, GetColor(elem,elem,elem));
		}
	}
	else
	{
		// �t�F�[�h�A�E�g��
		startX = static_cast<int>(Game::kScreenWidth * (1.0f - rate));
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int elem = GetRand(16) + 4;
			DrawLine(startX - GetRand(128), y, endX, y, GetColor(elem, elem, elem));
		}
	}
#endif
}

void SceneBase::drawLoading() const
{
	if (m_isDispLoading && !isLoaded())
	{
#if false
		for (int i = 0; i < 8; i++)
		{
			int x = GetRand(Game::kScreenWidth);
			int y = GetRand(Game::kScreenHeight);

			DrawString(x,y,"���[�h��",0xffffff);
		}
#endif
		float progress = getLoadProgress();
		if (progress >= 0.0f)
		{
			// ���[�h�i���̃f�o�b�O�\��
			constexpr int kBoxLeft = 120;
			constexpr int kBoxRight = Game::kScreenWidth - 120;
			constexpr int kBoxTop = Game::kScreenHeight - 160;
			constexpr int kBoxBottom = Game::kScreenHeight - 80;
			constexpr int kBoxLen = kBoxRight - kBoxLeft;
			DrawBox(kBoxLeft, kBoxTop, static_cast<int>(kBoxLeft + kBoxLen * progress), kBoxBottom, 0xffffff, true);
			DrawBox(kBoxLeft, kBoxTop, kBoxRight, kBoxBottom, 0xffffff, false);

			DrawFormatString(kBoxLeft + 8, kBoxBottom - 48, 0x000000, "���[�h���c");
			DrawFormatString(kBoxLeft + 8, kBoxBottom - 32, 0x000000, "%3.1f %%", progress * 100);
		}
	}
}

void SceneBase::drawCursor() const
{
	if (!m_isDispCursor)	return;

	int count = 0;
	int size = kCursorSize / 2;
	for (int i = 0; i < Mouse::getLogNum(); i++)
	{
		float rate = static_cast<float>(i) / static_cast<float>(Mouse::getLogNum() - 1);
		if (rate < 0.0f)	rate = 0.0f;
		if (rate > 1.0f)	rate = 1.0f;
		rate = 1.0f - rate;
		int alpha = static_cast<int>(255 * rate);

		Vec2 pos = Mouse::getPos(i);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawLine(static_cast<int>(pos.x), static_cast<int>(pos.y) - size,
			static_cast<int>(pos.x), static_cast<int>(pos.y) + size,
			0xffffff, 3);
		DrawLine(static_cast<int>(pos.x) - size, static_cast<int>(pos.y),
			static_cast<int>(pos.x) + size, static_cast<int>(pos.y),
			0xffffff, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		size -= 1;
		count++;
	}
}

bool SceneBase::isFadingIn() const
{
	if (m_fadeDir < 0)	return true;
	return false;
}

bool SceneBase::isFadingOut() const
{
	if (m_fadeDir > 0)	return true;
	return false;
}

void SceneBase::startFadeIn()
{
	m_fadeDir = -1;
	// �t�F�[�h�C�������͐F�A�v���C���[�����肵�Ȃ�(�O�̃V�[���̃t�F�[�h�A�E�g�����g�p����)
}

void SceneBase::startFadeOut()
{
//	Sound::getInstance().play("sceneChange");
	m_fadeDir = 1;
	m_fadePlayerKind = GetRand(Player::getKindNum() - 1);

	int colorNo = GetRand(kFadeColorNum - 1);
	m_fadeColor = kFadeColor[colorNo];
}
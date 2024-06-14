#include "Field.h"
#include "DxLib.h"
#include "game.h"
#include "Font.h"
#include "Message.h"
#include "Player.h"
#include "PlayerManager.h"

#include <string>
#include <cassert>

namespace
{
	// �}�b�v�`�b�v���
	constexpr int kChipWidth = 16;
	constexpr int kChipHeight = 16;
	// �`�b�v�ԍ�
	constexpr int kWallChipNo = 122;	// �v���C���[���Ԃ���ǂ̃`�b�v�ԍ�
	constexpr int kSoilChipNo = 29;	// �y�̃`�b�v�ԍ�
	constexpr int kLandChipNo = 7;	// �n�ʂ̃`�b�v�ԍ�

	// �n�ʂ�\�����鍂��
	constexpr int kFieldY = kChipHeight * 6;

	// �㉺�ǂ̈ʒu
	constexpr int kPipeTopY = -Game::kScreenHeight / 2 + kFieldY + kChipHeight;	// �n�ʂ̂�����
	constexpr int kPipeBottomY = Game::kScreenHeight / 2 - kChipHeight;

	// �@�����ꏊ�̐F
	constexpr unsigned int kDigColor = 0x4C2E30;

	// �@�錊�̃T�C�Y
	constexpr int kDigRadiusMin = 10;
	constexpr int kDigRadiusMax = 16;

	// ���̈ʒu�f�[�^�ő�ۑ���
	constexpr int kDigDataMax = 1024;

	// ���Ԋu�Ő�������
	constexpr int kDispDistanceY = 48+44;
	constexpr int kDispDistanceInterval = 100;

	constexpr int kDispDistanceArrowY = 96 + 44;

	// ���Ԋu���Ƃɓ�Փx�㏸(���[�g��)
	constexpr int kLevelUpDistanceY = 1000;
}

Field::Field(bool isDemo):
	m_handle(-1),
	m_graphW(0),
	m_graphH(0),
	m_chipNumX(0),
	m_chipNumY(0),
	m_lineNo(1),	// 0���[�g���͕\�����Ȃ�
	m_lineSin(0.0f),
	m_isDemo(isDemo)
{
	m_digData.resize(Game::kMaxPlayer);
}

Field::~Field()
{
}

void Field::init()
{
	// �O���t�B�b�N�f�[�^������𐶐�����
	GetGraphSize(m_handle, &m_graphW, &m_graphH);

	// �O���t�B�b�N�Ɋ܂܂��`�b�v�̐�
	m_chipNumX = m_graphW / kChipWidth;
	m_chipNumY = m_graphH / kChipHeight;

	initFieldLine();
}

void Field::update()
{
	Vec2 scroll = m_pPlayer->getScroll();
	// ���C���̓_��
	m_lineSin += 0.05f;
	if (m_lineSin > DX_TWO_PI_F)	m_lineSin -= DX_TWO_PI_F;

	int lineX = static_cast<int>(Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + (m_lineNo * kDispDistanceInterval) * 16.0f);
	if (lineX < 0 - 64)
	{
		m_lineNo++;
	}

	// �v���C���[�̌��݈ʒu����g�p�ς݂̃}�b�v�����폜���A
	// ���ꂩ��K�v�ɂȂ肻���ȃf�[�^��ǉ�����

	updateFieldLine();
}

void Field::draw()
{
	drawBg();

	// �@���������̏��
	for (auto& hole : m_digData)
	{
		for (auto& dig : hole)
		{
			Vec2 center = dig.pos;
			center += m_pPlayer->getScroll();
			DrawCircle(static_cast<int>(center.x), static_cast<int>(center.y), dig.radius, dig.color, true);
		}
	}

	// 1���C�����n�ʂ�`�悷��
	int indexX = kWallChipNo % m_chipNumX;
	int indexY = kWallChipNo / m_chipNumX;
	for (auto& line : m_fieldData)
	{
		int posX = static_cast<int>(line.x + m_pPlayer->getScroll().x);
		for (auto& chip : line.chip)
		{
			int posY = static_cast<int>(chip.y + m_pPlayer->getScroll().y);

			DrawRectGraph(posX, posY,
				indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
		}
	}

	drawDistance();
	
#if false
	// 200���[�g�����C���������e�X�g
	for (int i = 200; i < 5000; i += 200)
	{
		int lineX = Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + i * 16.0f;
		DrawLine(lineX, 0, lineX, Game::kScreenHeight, 0xff0000, 8);
	}
#endif
#if false
	// ���ʂɒn�ʃf�[�^����������Ă��Ȃ����`�F�b�N
	DrawFormatString(8, 640, 0xffffff, "Field line Num : %d", m_fieldData.size());
#endif
#if false
	Vec2 pos = Vec2{0,0};
	pos += m_pPlayer->getScroll();

	DrawRectGraph(static_cast<int>(pos.x), static_cast<int>(pos.y),
		indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
#endif
}

Rect Field::getMoveEnableRect(const Rect rect)
{
	Rect result;

	// �}�b�v�S�̂��ړ��\�ȏ�Ԃŏ�����
	result.setTop(rect.getCenter().y - Game::kScreenHeight / 2);
	result.setBottom(rect.getCenter().y + Game::kScreenHeight / 2);
	result.setLeft(rect.getCenter().x - Game::kScreenWidth / 2);
	result.setRight(rect.getCenter().x + Game::kScreenWidth / 2);

	// �㉺�����`�F�b�N
	for (auto& field : m_fieldData)
	{
		// ���E�������`�F�b�N���Đ�΂ɓ�����Ȃ����̂͏��O����
		if (field.x > rect.getRight())	continue;
		if (field.x + kChipWidth < rect.getLeft())	continue;

		for (auto& chip : field.chip)
		{
			// �v���C���[��艺�ɂ���u���b�N
			if (chip.y > rect.getBottom()-1)
			{
				if (result.getBottom()-1 > chip.y)
				{
					result.setBottom(static_cast<float>(chip.y));
				}
			}
			// �v���C���[����ɂ���u���b�N
			if (chip.y + kChipHeight < rect.getTop())
			{
				if (result.getTop() < chip.y + kChipHeight)
				{
					result.setTop(static_cast<float>(chip.y + kChipHeight));
				}
			}
		}
	}
	// �E�����`�F�b�N	�E�ɐi�ނ̂ō��̓`�F�b�N�s�v
	bool isEnd = false;
	for (auto& field : m_fieldData)
	{
		// ���ɂ���z�͏��O
		if (field.x < rect.getLeft())	continue;

		for (auto& chip : field.chip)
		{
			// ���E�ړ��œ�����Ȃ����̂����O
			if (chip.y > rect.getBottom() - 1)	continue;
			if (chip.y + kChipHeight < rect.getTop())	continue;

			// �����珇�ԂɃ`�F�b�N����̂ōŏ��̂����������炻���ŏI������OK
			result.setRight(static_cast<float>(field.x));
			isEnd = true;
			break;
		}
		if (isEnd)	break;
	}
	return result;
}

void Field::addDigData(Vec2 pos, unsigned int color, int playerNo)
{
	DigData data;
	data.pos = pos;
	data.radius = kDigRadiusMin + GetRand(kDigRadiusMax - kDigRadiusMin);
	data.color = color;
	m_digData[playerNo].push_back(data);
	if (m_digData[playerNo].size() > kDigDataMax)
	{
		m_digData[playerNo].pop_front();
	}
}

void Field::addStartDigData(Vec2 pos, unsigned int color, int playerNo)
{
	DigData data;
	data.pos = pos;
	data.radius = kDigRadiusMax;
	data.color = color;
	m_digData[playerNo].push_back(data);
	if (m_digData[playerNo].size() > kDigDataMax)
	{
		m_digData[playerNo].pop_front();
	}
}

bool Field::isCol(Vec2 pos)
{
	for (auto& line : m_fieldData)
	{
		if (line.x > pos.x)	continue;
		if (line.x + kChipWidth < pos.x)	continue;

		for (auto& chip : line.chip)
		{
			if (chip.y > pos.y)	continue;
			if (chip.y + kChipHeight < pos.y)	continue;

			return true;
		}
	}

	return false;
}

void Field::initFieldLine()
{
	Vec2 playerPos = m_pPlayer->getPlayer(0)->getPos();
	// ��ʍ�����㉺�̕ǂ�z�u����
	int posX = static_cast<int>(playerPos.x);
	posX -= Game::kScreenWidth / 2;
	int num = Game::kScreenWidth / kChipWidth;
	posX = addPipe(posX, num);

	if (isDemoPlay())
	{
		// ��Q���o�Ȃ�
		posX = addPipe(posX, 100);
		return;
	}

	// �ŏ���1/2�łǂ������̃p�^�[��
	if (GetRand(1))
	{
		// �����と�����ニ�[�g
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
	}
	else
	{
		// �と�����と�����[�g
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
	}
}

void Field::updateFieldLine()
{
	Vec2 scroll = m_pPlayer->getScroll();

	// ��ʊO�ɏo�����C�����폜���Ă���
	int deleteLineNum = 0;
	while (1)
	{
		int screenX = static_cast<int>(m_fieldData.front().x + scroll.x);
		if (screenX > 0 - kChipWidth)	break;

		m_fieldData.pop_front();
		deleteLineNum++;
	}

	// ���̃��C�����Ȃ��Ȃ肻���Ȃ�ǉ�����
	int posX = m_fieldData.back().x;
	if (posX + scroll.x < Game::kScreenWidth + 64)
	{
		addFieldBlock(posX + kChipWidth);
	}
}

Field::FieldLine Field::createLine(int posX)
{
	FieldLine lineData;
	lineData.x = posX;
	// ���ݐݒ蒆�̃��C���̃u���b�N�f�[�^�𐶐�(�Ƃ肠�����n�ʂ̂�)
	FieldChip chip;
	chip.y = 0;
	lineData.chip.push_back(chip);

	return lineData;
}

void Field::addFieldBlock(int startX)
{
	Vec2 scroll = m_pPlayer->getScroll();

	int x = startX;

	if (isDemoPlay())
	{
		// ��Q���o�Ȃ�
		x = addPipe(x, 40);
		return;
	}

	int randNum = GetRand(10);
	if (randNum == 0)	// 0
	{
		// ���b�L�[	�㉺�ȊO�����Ȃ�
		x = addPipe(x, 40);
	}
	else if (randNum <= 2)	// 1 2
	{
		// ���߂̃g���l��
		x = addPipe(x, 16);
		x = addHole(x, 24);
	}
	else if (randNum <= 4)	// 34
	{
		// �����ニ�[�g
		x = addPipe(x, 16);
		x = addUpperWall(x, 4);
		x = addPipe(x, 16);
		x = addUnderWall(x, 4);
	}
	else if (randNum <= 6)	// 5 6
	{
		// �と�����[�g
		x = addPipe(x, 16);
		x = addUnderWall(x, 4);
		x = addPipe(x, 16);
		x = addUpperWall(x, 4);
	}
	else	// 7 8 9 10
	{
		// ��������
		x = addPipe(x, 16);
		x = addHole(x, 4);
	}
}

int Field::addUpperWall(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// �㉺�̕ǐ���
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;
		FieldLine lineData;
		lineData.x = x;

		for(int j = 0; j < 20; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + kChipHeight * j;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - kChipHeight * j;
			lineData.chip.push_back(chip);
		}

		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addUnderWall(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// �㉺�̕ǐ���
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;
		FieldLine lineData;
		lineData.x = x;

		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < 20; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - kChipHeight * j;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addPipe(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// �㉺�̕ǐ���
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;

		FieldLine lineData;
		lineData.x = x;

		for(int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addHole(int startX, int lineNum)
{
	int holeY = GetRand(320) - 160 + (kPipeTopY + kPipeBottomY) / 2;

	// �㉺�̕ǐ���
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		FieldLine lineData;
		lineData.x = x;

		for (int y = kPipeTopY; y <= kPipeBottomY; y += kChipHeight)
		{
			// ����������
			if (y > (holeY - 64) && y < (holeY + 64))	continue;

			FieldChip chip;
			chip.y = y;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

void Field::drawBg()
{
	assert(m_pPlayer);
	int chipScrollX = static_cast<int>(m_pPlayer->getScroll().x) % kChipWidth;
	
	// ��ԏ�̃��C���ɂ͒n�ʂ�\��
	int indexX = kLandChipNo % m_chipNumX;
	int indexY = kLandChipNo / m_chipNumX;
	for (int x = 0; x < Game::kScreenWidth + kChipWidth; x += kChipWidth)	// �X�N���[������̂�1���C�����L���`��
	{
		DrawRectGraph(x + chipScrollX, kFieldY,
			indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
	}
	// �w�i��y�Ŗ��߂�
	indexX = kSoilChipNo % m_chipNumX;
	indexY = kSoilChipNo / m_chipNumX;
	for (int x = 0; x < Game::kScreenWidth + kChipWidth; x += kChipWidth)	// �X�N���[������̂�1���C�����L���`��
	{
		for (int y = kFieldY + kChipHeight; y < Game::kScreenHeight; y += kChipHeight)	// ��ԏ�̃��C���ɂ͒n�ʂ�`�悵�Ă���̂ł��̉��̃��C������
		{
			DrawRectGraph(x + chipScrollX, y,
				indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
		}
	}
}

void Field::drawDistance()
{
	//	int alpha = static_cast<int>(255 * (sinf(m_lineSin) * 0.5f + 0.5f));
	int distance = m_lineNo * kDispDistanceInterval;
	int lineX = static_cast<int>(Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + distance * 16.0f);

	// �����̕\��
	std::string dispDist = std::to_string(distance);
	if (distance == 1)
	{
		dispDist += Message::getInstance().get_c("MSG_COMMON_UNIT");
	}
	else
	{
		dispDist += Message::getInstance().get_c("MSG_COMMON_UNITS");
	}
	
	int width = Font::getStringWidth(dispDist.c_str(), Font::Id::DispDistance);
	int y = kDispDistanceY + static_cast<int>(16 * sinf(m_lineSin));
	Font::drawString(lineX - width / 2, y, dispDist.c_str(), 0xffffff, Font::Id::DispDistance);

	// ���
	y = kDispDistanceArrowY + static_cast<int>(16 * sinf(m_lineSin));
	DrawTriangle(lineX, y, 
				lineX + static_cast<int>(16 * sinf(m_lineSin)), y - 24,
				lineX - static_cast<int>(16 * sinf(m_lineSin)), y - 24, 0xff0000, true);
	DrawTriangle(lineX, y, 
				lineX + static_cast<int>(16 * sinf(m_lineSin)), y - 24,
				lineX - static_cast<int>(16 * sinf(m_lineSin)), y - 24, 0xffffff, false);

	y = 720-32 - static_cast<int>(16 * sinf(m_lineSin));
	DrawTriangle(lineX, y,
		lineX + static_cast<int>(16 * sinf(m_lineSin)), y + 24,
		lineX - static_cast<int>(16 * sinf(m_lineSin)), y + 24, 0xff0000, true);
	DrawTriangle(lineX, y,
		lineX + static_cast<int>(16 * sinf(m_lineSin)), y + 24,
		lineX - static_cast<int>(16 * sinf(m_lineSin)), y + 24, 0xffffff, false);
}

bool Field::isDemoPlay()
{
	return m_isDemo;
}


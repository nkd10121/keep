#include "Font.h"
#include "DxLib.h"
#include <vector>
#include <string>
#include <cassert>
#include "game.h"
#include "StrUtil.h"

namespace
{
	// �ǂݍ��ރt�H���g�t�@�C����
	const LPCSTR kFontDataPath[] =
	{
	//	"data/Makinas-4-Flat.otf",
	//	"data/font/Makinas-4-Square.otf",
	//	"data/font/NewDokabenFont_.otf",
		"data/font/GN-KillGothic-U-KanaNA.ttf",
	};
	
	// �ǂݍ��񂾃t�H���g�̃f�[�^
	// �n���h���ȊO�ɂ��`��Ɏg�������ȃf�[�^�����W���Ă���
	struct FontInfo
	{
		int					handle;			// �t�H���g�̃n���h��
		// �����\���Ɏg��
		std::vector<int>	numWidth;		// 0~9�̊e�����̉���
		int					numMaxWidth;	// �t�H���g�̐����̂����A��ԉ����̑傫�����̂̃T�C�Y
	};

	// �t�H���g�̃n���h��
//	std::vector<int> fontHandle;
	std::vector<FontInfo> fontInfo;

	// �t�H���g�����f�[�^
	struct FontData
	{
		const char* name;
		int	size;
		int	thick;		// ����	-1�Ńf�t�H���g
		int type;		// DX_FONTTYPE_XXX	-1�Ńf�t�H���g
	};

	constexpr FontData data[] =
	{
		// Size200_8
		{
			"GN-�L���SU����NA",
			200,
			8,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size96_8
		{
			"GN-�L���SU����NA",
			96,
			8,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size96_4
		{
			"GN-�L���SU����NA",
			96,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size64_4
		{
			"GN-�L���SU����NA",
			64,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size48_4
		{
			"GN-�L���SU����NA",
			48,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size32_4
		{
			"GN-�L���SU����NA",
			32,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size24_4
		{
			"GN-�L���SU����NA",
			24,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size16_4
		{
			"GN-�L���SU����NA",
			16,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Normal
		{
			"�l�r�@�S�V�b�N",
			16,
			-1,
			-1
		},		
	};
	static_assert(_countof(data) == static_cast<int>(Font::Id::Num));
}

namespace Font
{
#if false
	void setup()
	{
		// �t�H���g�̃��[�h
		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else {
				// �t�H���g�Ǎ��G���[����
				MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
			}
		}
		
		// �t�H���g�f�[�^�̐���
		for (int i = 0; i < static_cast<int>(Font::Id::Num); i++)
		{
			FontInfo info;
			info.handle = CreateFontToHandle(data[i].name, data[i].size, data[i].thick, data[i].type);
			info.numMaxWidth = 0;
			for (int i = 0; i < 10; i++)
			{
				std::string str = std::to_string(i);
				int width = GetDrawFormatStringWidthToHandle(info.handle, str.c_str());
				info.numWidth.push_back(width);
				info.numMaxWidth = max(info.numMaxWidth, width);	// ��ԉ����̍L�������̉���
			}
			fontInfo.push_back(info);
		}
	}
	void release()
	{
		// �t�H���g�f�[�^�̍폜
		for (int i = 0; i < fontInfo.size(); i++)
		{
			DeleteFontToHandle(fontInfo[i].handle);
		}

		// �t�H���g�̃A�����[�h
		for (auto& fontPath : kFontDataPath)
		{
			if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {
			}
			else {
				MessageBox(NULL, "remove failure", "", MB_OK);
			}
		}
	}
#else
	void loadStart()
	{
		// �t�H���g�̃��[�h
		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else {
				// �t�H���g�Ǎ��G���[����
				MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
			}
		}
		// �t�H���g�f�[�^�̐���
		SetUseASyncLoadFlag(true);
		for (int i = 0; i < static_cast<int>(Font::Id::Num); i++)
		{
			FontInfo info;
			info.handle = CreateFontToHandle(data[i].name, data[i].size, data[i].thick, data[i].type);
			info.numMaxWidth = 0;
			fontInfo.push_back(info);
		}
		SetUseASyncLoadFlag(false);
	}
	void unload()
	{
		// �t�H���g�f�[�^�̍폜
		for (int i = 0; i < fontInfo.size(); i++)
		{
			DeleteFontToHandle(fontInfo[i].handle);
		}

		// �t�H���g�̃A�����[�h
		for (auto& fontPath : kFontDataPath)
		{
			if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {
			}
			else {
				MessageBox(NULL, "remove failure", "", MB_OK);
			}
		}
	}

	bool isLoaded()
	{
		for (auto& info : fontInfo)
		{
			if (CheckHandleASyncLoad(info.handle))	return false;
		}
		return true;
	}
	void collectData()
	{
		for (auto& info : fontInfo)
		{
			info.numWidth.clear();
			info.numMaxWidth = 0;
			for (int i = 0; i < 10; i++)
			{
				std::string str = std::to_string(i);
				int width = GetDrawFormatStringWidthToHandle(info.handle, str.c_str());
				info.numWidth.push_back(width);
				info.numMaxWidth = max(info.numMaxWidth, width);	// ��ԉ����̍L�������̉���
			}
		}
	}
#endif
	int getHandle(Font::Id id)
	{
		return fontInfo[static_cast<int>(id)].handle;
	}
	int getSize(Id id)
	{
		return data[static_cast<int>(id)].size;
	}
	int getStringWidth(const char* pText, Id id)
	{
		return GetDrawStringWidthToHandle(pText, static_cast<int>(strlen(pText)), getHandle(id));
	}
	int getStringWidth(const char* pText, int handle, int kerning)
	{
		int width = 0;
		std::vector<std::string>	splitText = StrUtil::splitString(pText);

		for (auto& chr : splitText)
		{
			width += GetDrawStringWidthToHandle(chr.c_str(), static_cast<int>(strlen(chr.c_str())), handle);
			width += kerning;
		}
		// �Ō�̕����̃J�[�j���O�͕s�v�Ȃ̂�1�������߂�
		width -= kerning;

		return width;
	}
	void drawString(int x, int y, const char* pText, int color, Id id)
	{
		DrawStringToHandle(x, y, pText, color, Font::getHandle(id));
	}
	void drawStringCenter(int y, const char* pText, int color, Id id)
	{
		int width = Font::getStringWidth(pText, id);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, y, pText, color, Font::getHandle(id));
	}
	// �����̓����\��	�����P��`�悷��
	void drawSingleNum(int x, int y, int num, int color, Id id)
	{
		assert(num >= 0);
		assert(num < 10);
		int width = fontInfo[static_cast<int>(id)].numWidth[num];
		int maxWidth = fontInfo[static_cast<int>(id)].numMaxWidth;
		int offset = (maxWidth - width) / 2;
		DrawStringToHandle(x + offset, y, std::to_string(num).c_str(), color, Font::getHandle(id));
	}
	void drawTimeFromFrame(int x, int y, int frameCount, int color, Id id)
	{
		int width = fontInfo[static_cast<int>(id)].numMaxWidth;
		int msec = frameCount % 60;
		msec = static_cast<int>(msec * 16.6667f);
		int sec = frameCount / 60;
		int minit = sec / 60;
		sec %= 60;

		// �J���X�g
		if (minit > 99)
		{
			minit = 99;
			sec = 59;
			msec = 999;
		}

		int posX = x;
		int posY = y;
		// ���̕�����\��
		if (minit < 10)
		{
			// 1��
			posX += width;	// 10�̈ʂ͔�΂�

			drawSingleNum(posX, posY, minit, color, id);
			posX += width;
		}
		else
		{
			drawSingleNum(posX, posY, minit / 10, color, id);
			posX += width;
			drawSingleNum(posX, posY, minit % 10, color, id);
			posX += width;
		}
		DrawStringToHandle(posX, posY, ":", color, Font::getHandle(id));
		posX += GetDrawStringWidthToHandle(":", static_cast<int>(strlen(":")), Font::getHandle(id));
		// �b�̕�����\��
		drawSingleNum(posX, posY, sec / 10, color, id);
		posX += width;
		drawSingleNum(posX, posY, sec % 10, color, id);
		posX += width;
		DrawStringToHandle(posX, posY, ".", color, Font::getHandle(id));
		posX += GetDrawStringWidthToHandle(".", static_cast<int>(strlen(".")), Font::getHandle(id));
		// �~���b������\��
	//	msec = 999;
		drawSingleNum(posX, posY, msec / 100, color, id);
		posX += width;
		msec %= 100;
		drawSingleNum(posX, posY, msec / 10, color, id);
		posX += width;
		drawSingleNum(posX, posY, msec % 10, color, id);
		posX += width;
	}
	int getDrawTimeWidth(Id id)
	{
		int result = 0;
		int width = fontInfo[static_cast<int>(id)].numMaxWidth;
		// ��2���A�b2���A�~���b3��
		result += width * 7;
		result += GetDrawStringWidthToHandle(":", static_cast<int>(strlen(":")), Font::getHandle(id));
		result += GetDrawStringWidthToHandle(".", static_cast<int>(strlen(".")), Font::getHandle(id));

		return result;
	}
}
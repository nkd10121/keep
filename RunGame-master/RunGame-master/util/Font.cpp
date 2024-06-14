#include "Font.h"
#include "DxLib.h"
#include <vector>
#include <string>
#include <cassert>
#include "game.h"
#include "StrUtil.h"

namespace
{
	// 読み込むフォントファイル名
	const LPCSTR kFontDataPath[] =
	{
	//	"data/Makinas-4-Flat.otf",
	//	"data/font/Makinas-4-Square.otf",
	//	"data/font/NewDokabenFont_.otf",
		"data/font/GN-KillGothic-U-KanaNA.ttf",
	};
	
	// 読み込んだフォントのデータ
	// ハンドル以外にも描画に使いそうなデータを収集しておく
	struct FontInfo
	{
		int					handle;			// フォントのハンドル
		// 等幅表示に使う
		std::vector<int>	numWidth;		// 0~9の各数字の横幅
		int					numMaxWidth;	// フォントの数字のうち、一番横幅の大きいもののサイズ
	};

	// フォントのハンドル
//	std::vector<int> fontHandle;
	std::vector<FontInfo> fontInfo;

	// フォント生成データ
	struct FontData
	{
		const char* name;
		int	size;
		int	thick;		// 太さ	-1でデフォルト
		int type;		// DX_FONTTYPE_XXX	-1でデフォルト
	};

	constexpr FontData data[] =
	{
		// Size200_8
		{
			"GN-キルゴUかなNA",
			200,
			8,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size96_8
		{
			"GN-キルゴUかなNA",
			96,
			8,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size96_4
		{
			"GN-キルゴUかなNA",
			96,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size64_4
		{
			"GN-キルゴUかなNA",
			64,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size48_4
		{
			"GN-キルゴUかなNA",
			48,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size32_4
		{
			"GN-キルゴUかなNA",
			32,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size24_4
		{
			"GN-キルゴUかなNA",
			24,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Size16_4
		{
			"GN-キルゴUかなNA",
			16,
			4,
			DX_FONTTYPE_ANTIALIASING_EDGE_8X8
		},
		// Normal
		{
			"ＭＳ　ゴシック",
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
		// フォントのロード
		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else {
				// フォント読込エラー処理
				MessageBox(NULL, "フォント読込失敗", "", MB_OK);
			}
		}
		
		// フォントデータの生成
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
				info.numMaxWidth = max(info.numMaxWidth, width);	// 一番横幅の広い数字の横幅
			}
			fontInfo.push_back(info);
		}
	}
	void release()
	{
		// フォントデータの削除
		for (int i = 0; i < fontInfo.size(); i++)
		{
			DeleteFontToHandle(fontInfo[i].handle);
		}

		// フォントのアンロード
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
		// フォントのロード
		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else {
				// フォント読込エラー処理
				MessageBox(NULL, "フォント読込失敗", "", MB_OK);
			}
		}
		// フォントデータの生成
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
		// フォントデータの削除
		for (int i = 0; i < fontInfo.size(); i++)
		{
			DeleteFontToHandle(fontInfo[i].handle);
		}

		// フォントのアンロード
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
				info.numMaxWidth = max(info.numMaxWidth, width);	// 一番横幅の広い数字の横幅
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
		// 最後の文字のカーニングは不要なので1文字分戻す
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
	// 数字の等幅表示	数字１つを描画する
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

		// カンスト
		if (minit > 99)
		{
			minit = 99;
			sec = 59;
			msec = 999;
		}

		int posX = x;
		int posY = y;
		// 分の部分を表示
		if (minit < 10)
		{
			// 1桁
			posX += width;	// 10の位は飛ばす

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
		// 秒の部分を表示
		drawSingleNum(posX, posY, sec / 10, color, id);
		posX += width;
		drawSingleNum(posX, posY, sec % 10, color, id);
		posX += width;
		DrawStringToHandle(posX, posY, ".", color, Font::getHandle(id));
		posX += GetDrawStringWidthToHandle(".", static_cast<int>(strlen(".")), Font::getHandle(id));
		// ミリ秒部分を表示
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
		// 分2桁、秒2桁、ミリ秒3桁
		result += width * 7;
		result += GetDrawStringWidthToHandle(":", static_cast<int>(strlen(":")), Font::getHandle(id));
		result += GetDrawStringWidthToHandle(".", static_cast<int>(strlen(".")), Font::getHandle(id));

		return result;
	}
}
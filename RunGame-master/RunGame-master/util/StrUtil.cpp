#include "StrUtil.h"
#include <cassert>

namespace
{
	
}

namespace StrUtil
{
	std::vector<std::string> splitString(const std::string str)
	{
		std::vector<std::string>	result;

		std::string temp = str;
		int byteCount = 0;
		while (1)
		{
			if (byteCount > temp.size())
			{
				// 終了
				break;
			}

			std::string chr;	// 1文字分のデータ

			// 文字のバイト数チェック
			int size = 0;
			unsigned char charData = temp[byteCount];	// チェックする文字
			if (charData < 0x80)
			{
				size = 1;
			}
			else
			{
				size = 2;
			}
			// 必要場分のみ切り取り
			chr = temp.substr(byteCount, size);

			// １文字進める
			byteCount += size;
			if (chr != "\0")	// 除外する文字
			{
				result.push_back(chr);
			}
		}

		return result;
	}
}
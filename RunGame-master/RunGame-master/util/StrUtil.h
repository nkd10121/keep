#pragma once
#include <string>
#include <vector>

// 文字列便利関数
namespace StrUtil
{
	// 文字列を1文字ずつ分割したvectorにする
	// 3バイト以上の文字は非対応	最後の\0は取り除く
	std::vector<std::string> splitString(const std::string str);
}

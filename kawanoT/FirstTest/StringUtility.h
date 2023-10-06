#pragma once
#include <string>

class StringUtility
{
public:
	/// <summary>
	/// ここに説明
	/// </summary>
	/// <param name="a">引数1の説明</param>
	/// <param name="b">引数2の説明</param>
	/// <param name="c">引数3の説明</param>
	/// <returns> true:trueの時の状態 , false:falseの時の状態</returns>
	bool dummy(int a, int b, int c)
	{

	}


	/// <summary>
	/// マルチバイト文字列からワイド文字列への変換
	/// </summary>
	/// <param name="str">変換元のマルチバイト文字列</param>
	/// <returns>変換後のワイド文字列</returns>
	static std::wstring
		StringToWString(const std::string& str);
};


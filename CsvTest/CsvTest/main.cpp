#include <iostream>
#include <cassert>
// 今回使うのに必要
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Data
{
	int stageNum;
	int enemyNum;
	int enemyKind;
	int enemyFrame;
};

std::vector<std::string> Split(std::string str, const char sprit)
{
	std::vector<std::string> result;

	// 文字分割でどこから始めるかの位置
	int first = 0;
	// 文字分割でどこまで取得するかの位置
	int last = str.find_first_of(sprit);

	while(first < str.size())
	{
		// 区切ったものを結果に入れていく
		std::string subStr(str, first, last - first);

		// 文字を追加
		result.push_back(subStr);

		// 位置更新
		first = last + 1;
		last = str.find_first_of(sprit, first);
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

int main()
{
	// 取得する文字列を入れておく用の変数
	std::string strBuf;
	// 取得した文字列を分割したものを入れておく用の変数
	std::vector<std::string> strConmaBuf;


	Data data;


	// ファイル読み込み
	std::ifstream ifs("test.csv");
	if (!ifs)
	{
		assert(false);
		return 0;
	}

//	// 読み込んだファイルから１行ずつ読み込む
//	std::getline(ifs, strBuf);

	// 全行読み込むまで繰り返す
	while (std::getline(ifs, strBuf))
	{
#if true
		strConmaBuf = Split(strBuf, ',');

		int idx = 0;
		for (const auto& str : strConmaBuf)
		{
			//data.stageNum = stoi(str);
			std::cout << str.c_str() << "," << std::flush;
		}

		//std::cout << strConmaBuf[0] << std::flush;

#else
		std::cout << strBuf.c_str() << std::flush;
#endif

		std::cout << std::endl;
	}

	// ファイル閉じる
	ifs.close();

	return 0;
}
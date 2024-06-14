#include "Message.h"

#include <fstream>
#include <sstream>
#include <vector>

Message* Message::m_instance = nullptr;

namespace
{
	const char* const kMessageFilename = "data/csv/Message.csv";


	// csvデータの,で文字列を分割する
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		while (getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}

void Message::load(LANG lang)
{
	std::ifstream ifs(kMessageFilename);

	m_data.clear();

	m_current = lang;

	std::string line;
	while (std::getline(ifs, line))
	{
		std::vector<std::string> strvec = split(line, ',');

		m_data[strvec.at(0)] = strvec.at(1+lang);

	//	m_data[strvec.at(0)] = strvec.at(1);	// とりあえず日本語のみ
	//	m_data[strvec.at(0)] = strvec.at(2);	// 英語テスト
	}
}

std::string Message::get(std::string id)
{
	return m_data[id];
}

const char* Message::get_c(std::string id)
{
	return m_data[id].c_str();
}

#pragma once

#include <string>
#include <map>

// シングルトンを使用したメッセージデータ管理クラス
class Message
{
public:
	enum LANG
	{
		LANG_JP,	// 日本語
		LANG_US,	// 英語(アメリカ)

		LANG_NUM
	};
private:
	Message() = default;
	virtual ~Message() = default;

	static Message* m_instance;
public:
	// コピーコンストラクタの禁止
	Message(const Message&) = delete;
	Message& operator=(const Message&) = delete;
	Message(Message&&) = delete;
	Message& operator=(Message&&) = delete;

	static Message& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new Message;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}
public:
	// メッセージデータの初回読み込み
	void load(LANG lang = LANG_JP);

	// 言語の変更(内部で読み込みが走る)

	// メッセージの取得
	std::string get(std::string id);
	const char* get_c(std::string id);

	// 現在の使用言語取得
	LANG getCurrentLanguage() const  { return m_current; }

private:
	std::map<std::string, std::string>	m_data;
	LANG	m_current;
};


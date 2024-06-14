#pragma once

#include <string>
#include <map>

// �V���O���g�����g�p�������b�Z�[�W�f�[�^�Ǘ��N���X
class Message
{
public:
	enum LANG
	{
		LANG_JP,	// ���{��
		LANG_US,	// �p��(�A�����J)

		LANG_NUM
	};
private:
	Message() = default;
	virtual ~Message() = default;

	static Message* m_instance;
public:
	// �R�s�[�R���X�g���N�^�̋֎~
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
	// ���b�Z�[�W�f�[�^�̏���ǂݍ���
	void load(LANG lang = LANG_JP);

	// ����̕ύX(�����œǂݍ��݂�����)

	// ���b�Z�[�W�̎擾
	std::string get(std::string id);
	const char* get_c(std::string id);

	// ���݂̎g�p����擾
	LANG getCurrentLanguage() const  { return m_current; }

private:
	std::map<std::string, std::string>	m_data;
	LANG	m_current;
};


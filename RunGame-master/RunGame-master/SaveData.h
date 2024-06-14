#pragma once
// �V���O���g�����g�p�����Z�[�u�f�[�^�Ǘ��N���X
class SaveData
{
public:
	// �Z�[�u�f�[�^�ɕۑ�����t���O
	enum GameFlag
	{
		TutorialEnd = 0,

	//	// �A�`�[�u�����g�֘A	���l�͕ύX����Ă��邩��
	//	Achieve_TutorialClear,	// �`���[�g���A�����Ō�܂Ńv���C����
	};
#if false
	// �ݒ�
	enum ConfigFlag
	{
		FullScreen = 0,	// �t���X�N���[���ݒ�
		Vibration = 1,	// �U��ONOFF
	};
#endif
	// �����L���O�f�[�^�c���l��
	static constexpr int kSaveRankDataNum = 10;
	
private:
	SaveData() = default;
	virtual ~SaveData() = default;

	static SaveData* m_instance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	SaveData(const SaveData&) = delete;
	SaveData& operator=(const SaveData&) = delete;
	SaveData(SaveData&&) = delete;
	SaveData& operator=(SaveData&&) = delete;

	static SaveData& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new SaveData;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}
public:
	// �f�[�^�̓ǂݍ���
	void load();
	// �Z�[�u�f�[�^�̏�������
	void write();

	// �v���C�f�[�^�̐ݒ�	�������݂͍s��Ȃ��̂Őݒ肪�I�������write()����
	void gameFlagOn(GameFlag flag);
	void gameFlagOff(GameFlag flag);
	// �w�肵���t���O�������Ă��邩
	bool isGameOn(GameFlag flag);

	// �����L���O�擾	0~kSaveRankDataNum-1�@���w�肵�Ď擾
	int getRankPlayerKind(int rank);
	int getRankPlayerScore(int rank);

	// �X�R�A�̓o�^	�����N�C�������炻�̏��ʂ�0~kSaveRankDataNum-1�ŕԂ�	����Ȃ�������-1
	int entryScore(int score, int playerKind);


	// �A�`�[�u�����g�֘A
	void updateAchieve();	// �v���C�L�^���`�F�b�N���ăA�`�[�u�����g�̃t���O�𗧂Ă�

	// �Z�[�u�f�[�^��V�K�쐬���ď㏑��(�V�K�ۑ�)
	void createNewData();

#ifdef _DEBUG
	// �S�Ẵt���O��ON�ɂ���
	void setAllFlag();
#endif

private:
	void clearData();
	// �t���OON,OFF
	// isOn:�@true�Ńt���O�𗧂Ă�Afalse�ŗ��Ƃ�
	void setFlag(GameFlag flag, bool isOn);

private:
	struct RankData
	{
		int playerKind;
		int score;
		unsigned int reserved0 = 0;	// �\���̈�
		unsigned int reserved1 = 0;	// �\���̈�
	};

	// �ۑ�����Z�[�u�f�[�^�{��
	struct DataCore
	{
		int version = 0;		// �f�[�^�̃o�[�W����
		// 1�r�b�g�̃t���O
		unsigned int gameFlag = 0;	// �e��t���O(MAX32)
		unsigned int reserved0 = 0;	// �\���̈�
		unsigned int reserved1 = 0;	// �\���̈�

		// �����L���O
		RankData rankData[kSaveRankDataNum];
	};

private:
	DataCore m_data;
};


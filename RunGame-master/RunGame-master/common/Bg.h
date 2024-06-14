#pragma once
#include <vector>
#include <list>
#include <memory>

class EffectPlayer;
class Bg
{
public:
	Bg();
	virtual ~Bg();

	void load();
	void unload();
	bool isLoaded();

	void update();

	void drawBg();		// �X�N���[���w�i
	void drawPlayer();	// �v���C���[���o

	void drawAll();		// drawBg��drawPlayer�𗼕��s��

	// �g�p����w�i�f�[�^�̌���
	void setTileKind(int kind) { m_bgTileKind = kind; }
	void setTileKindRandom();	// �����_���Ɍ���

	// �v���C���[�����Ԋu�̐ݒ�
	void setPlayerInterval(int interval) { m_playerInterval = interval; }	// ���t���[���Ԋu�Ńv���C���[�𐶐����邩
	void setPlayerCreateNum(int num) { m_playerCreateNum = num; }			// �����������ɉ��̐������邩

	// �v���C���[��1�̐���
	void addPlayer();

private:
	std::vector<int>	m_handle;
	int	m_scroll;
	int m_bgTileKind;


	// ���o�p�v���C���[
	std::list<std::shared_ptr<EffectPlayer>>	m_pPlayer;
	int m_playerCreateFrameCount;

	// ���o�v���C���[�������[��
	int m_playerInterval;
	int m_playerCreateNum;
};


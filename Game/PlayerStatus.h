#pragma once
//�v���C���[�̃X�e�[�^�X���Ǘ�����
class PlayerStatus : public IGameObject
{

public:
	PlayerStatus();
	~PlayerStatus();
	//IGameObject��Start�֐����I�[�o�[���C�h����B  
	bool Start();
	//IGameObject��Update�֐����I�[�o�[���C�h����B  
	void Update();
	//�X�e�[�W1,2�̃v���C���[�̃��C�t��ݒ�
	void SetHeart(const int& heart)
	{
		m_playerheart = heart;
	}
	//�X�e�[�W3�̃v���C���[�̃��C�t���擾
	void SetLife(const int& life)
	{
		m_playerlife = life;
	}
	//�X�e�[�W1,2�̃v���C���[�̃��C�t���擾
	int GetHeart() const
	{
		return m_playerheart;
	}
	//�X�e�[�W3�̃v���C���[�̃��C�t���擾
	int GetLife() const
	{
		return m_playerlife;
	}
private:
	int m_playerheart = 5;
	int m_playerlife = 10;
};
#pragma once
//�X�e�[�W�I����X�e�[�W�I���̓��e��Game.cpp�ɔ��f������N���X
class StageKanri : public IGameObject 
{
public:
	StageKanri();
	~StageKanri();
	//IGameObject��Start�֐����I�[�o�[���C�h����B  
	bool Start();
	//IGameObject��Update�֐����I�[�o�[���C�h����B  
	void Update();
	//�X�e�[�W��ݒ�
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
	//�X�e�[�W�i���o�[���擾
	int GetStageNumber() const
	{
		return m_stagenumber;
	}
	//�X�e�[�W�̃N���A�����擾
	bool GetClear(const int& number) const
	{
		return Clear[number];
	}
	//�X�e�[�W�����擾
	int GetStage() const
	{
		return m_stage;
	}
	//�X�e�[�W�N���A!
	void StageClear()
	{
		Clear[m_stagenumber-1] = true;
	}
private:
	//Stage�I��
	static const int m_stage = 3;
	int m_stagenumber =1;
	bool Clear[m_stage] = { false,false,false};
};

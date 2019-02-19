#pragma once
//�X�e�[�W�I����X�e�[�W�I���̓��e��Game.cpp�ɔ��f������N���X
class Sound : public IGameObject
{
public:
	Sound();
	~Sound();
	void State();
	//IGameObject��Start�֐����I�[�o�[���C�h����B  
	bool Start();
	//IGameObject��Update�֐����I�[�o�[���C�h����B  
	void Update();
	//�Đ��\���BGM���Z�b�g
	void SetBGM(const int& state)
	{
		m_state2 = state;
	}
private:
	prefab::CSoundSource* m_bgmSoundSource;
	//���ݍĐ����Ă����
	int m_state1 = 0;
	//�Đ��\��̋�
	int m_state2 = 0;
};
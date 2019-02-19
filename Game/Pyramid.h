#pragma once
class Pyramid : public IGameObject
{
public:
	//�����o�֐��B
	Pyramid();
	~Pyramid();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�ړ����x��ݒ�
	void SetMovespeed(const CVector3& speed)
	{
		m_movespeed = speed;
	}
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B										
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;						//�^�C�}�[�B
	CVector3 m_scale = { 8.0f,8.0f,8.0f };
	int m_deletetime;
};
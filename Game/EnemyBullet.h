#pragma once
class EnemyBullet : public IGameObject
{
public:
	//�����o�֐��B
	EnemyBullet();
	~EnemyBullet();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	//�ړ����x��ݒ�
	void SetMovespeed(const CVector3& speed) {
		m_movespeed = speed;
	}
	//�폜���Ԃ�ݒ�
	void SetDeletetime(const int& time) {
		m_deletetime = time;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B 												
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;						//�^�C�}�[�B						//�e�̑傫��
	CVector3 m_scale = { 0.55f,0.55f,0.55f };
	int m_deletetime;
};
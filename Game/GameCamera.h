#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//�J�����̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�J�����̒����_���擾
	CVector3 GetTarget() const
 	{
		return m_target;
	}
	//�J������y���̊p�x���擾
	float GetDegree() const 
	{
		return m_degreexz;
	}
private:
	//�J�����̍��W����ђ����_�̌v�Z
	void Hutu();
	CVector3 m_toPos = { 0.0f, 0.0f, 0.0f };
	//�~�̒��S���W(�v���C���[�̍��W)
	CVector3 m_playerposition;
	//�p�x
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	//��]���x
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//���a
	const float m_r = 170.0f;
	//�p�x�����W�A���P��(��)�ɒ��������
	double m_radianx;
	double m_radiany;
	//�����_
	CVector3 m_target;
	//�J�����̍��W
	CVector3 m_position;
	Player * m_player;	//�v���C���[�B
};

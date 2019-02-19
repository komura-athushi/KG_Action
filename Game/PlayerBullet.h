#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class PlayerBullet : public IGameObject
{
public:
	//�����o�֐��B
	PlayerBullet();
	~PlayerBullet();
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
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B 												
	prefab::CEffect* m_effect = nullptr;
	int m_timer = 0;						//�^�C�}�[�B					//�e�̑傫��
	CVector3 m_scale;
};
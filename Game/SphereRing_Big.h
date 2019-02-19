#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class SphereRing;
class Boss;
class SphereRing_Big : public IGameObject
{
public:
	//�����o�֐��B
	SphereRing_Big();
	~SphereRing_Big();
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
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B										
	prefab::CEffect* m_effect = nullptr;
	int m_timer = 0;						//�^�C�}�[�B
	int m_sphereringtimer = 0;
	int m_sphereringcount = 0;
	CVector3 m_scale = { 2.5f,2.5f,2.5f };
	SphereRing* m_spherering;
	Boss* m_boss;
};
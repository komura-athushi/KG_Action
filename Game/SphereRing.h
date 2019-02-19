#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class SphereRing : public IGameObject
{
public:
	//�����o�֐��B
	SphereRing();
	~SphereRing();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�ړ��̖ڕW�̍��W��ݒ�
	void SetGoalPosition(const CVector3& goalpos)
	{
		m_goalposition = goalpos;
	}
	//�S�[�X�g���擾
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_protposition = CVector3::Zero;
	//�{�X�̍��W����ړ��������̒�~����ꏊ
	CVector3 m_goalposition = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	CPhysicsGhostObject m_ghostObject;
	int m_timer = 0;						//�^�C�}�[�B
	//m_position.x���{���邩-���邩										
	bool m_plusXZ = true;
	CVector3 m_scale;
	// �񎟊֐��̊e�萔 y=-a(x-b)^2+c m_a��y�̈ړ����x m_c��y�̍ő�l m_b��y���ő�l�̎���-x�̒l
	float m_a;
	float m_b,m_b2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	float m_c=300.0f;
	//x�����z�̈ړ����x
	float m_smovespeedX;
	float m_smovespeedZ;
	bool m_move = true;
};
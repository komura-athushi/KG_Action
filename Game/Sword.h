#pragma once
#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Sword : public IGameObject
{
public:
	//�����o�֐��B
	Sword();
	~Sword();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//��]���x��ݒ�
	void SetSdegree(const float& sdegree)
	{
		m_sdegree = sdegree;
	}
	//�S�[�X�g���擾
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 0.0f,50.0f,0.0f };			//���W�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	CVector3 m_scale = { 5.0f,5.0f,7.5f };
	CPhysicsGhostObject m_ghostObject;
	float m_degree = 0.0f;
	float m_sdegree = 1.9f;
	CVector3 m_tyusin = CVector3::Zero;
	float const m_r = 200.0f;
};

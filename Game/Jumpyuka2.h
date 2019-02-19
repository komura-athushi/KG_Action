#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
//��ɏ���Y���ɃL���������
class Jumpyuka2 : public IGameObject
{
public:
	//�����o�֐��B
	Jumpyuka2();
	~Jumpyuka2();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	CPhysicsGhostObject* GetGhostObject() 
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 0.0f,50.0f,0.0f };			//���W�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;			//!<�ÓI�����I�u�W�F�N�g�B
	CPhysicsGhostObject m_ghostObject;
};
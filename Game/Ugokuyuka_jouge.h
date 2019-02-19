#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_jouge : public IGameObject
{
public:
	//�����o�֐��B
	Ugokuyuka_jouge();
	~Ugokuyuka_jouge();
	bool Start();
	void Update();
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//���W�B
	CVector3 m_protposition = m_position;
	CVector3 m_lastframposition = CVector3::Zero;
	CVector3 m_movespeed = { 0.0f,2.0f,0.0f };
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;			//!<�ÓI�����I�u�W�F�N�g�B
	CPhysicsGhostObject m_ghostObject;
};
#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Goal : public IGameObject
{
public:
	//�����o�֐��B
	Goal();
	~Goal();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//���W�B
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;			//!<�ÓI�����I�u�W�F�N�g�B
};
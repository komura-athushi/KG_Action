#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_yoko3 : public IGameObject
{
public:
	//�����o�֐��B
	Ugokuyuka_yoko3();
	~Ugokuyuka_yoko3();
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
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//1�t���[���O�̍��W���擾
	CVector3 GetLastFramPosition() const
	{
		return m_lastframposition;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�S�[�X�g���擾
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//���W�B
	CVector3 m_protposition = m_position;
	CVector3 m_lastframposition = CVector3::Zero;
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	CVector3 m_movespeed=CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;					//!<�ÓI�����I�u�W�F�N�g�B
	CPhysicsGhostObject m_ghostObject;
	int m_number;
    float m_movespeedX;
};
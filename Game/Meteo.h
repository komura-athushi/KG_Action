#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Meteo : public IGameObject
{
public:
	//�����o�֐��B
	Meteo();
	~Meteo();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�S�[�X�g���擾
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B 												
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;						//�^�C�}�[�B									//�e�̑傫��
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	int m_deletetime;
	CPhysicsGhostObject m_ghostObject;
};
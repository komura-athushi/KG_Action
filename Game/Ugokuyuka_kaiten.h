#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_kaiten : public IGameObject
{
public:
	//�����o�֐��B
	Ugokuyuka_kaiten();
	~Ugokuyuka_kaiten();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_tyusin = pos;
	}
	//�ړ����x��ݒ�
	void SetSdegree(const float& sdegree)
	{
		m_sdegree = sdegree;
	}
	//�i���o�[��ݒ�
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
	//void PostRender(CRenderContext& renderContext);
	CVector3 m_tyusin = CVector3::Zero;
	float m_degree = 0.0f;
	//���a
	float m_r = 400.0f;
	CVector3 m_position = m_tyusin;			//���W�B
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	CVector3 m_lastframposition = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;					//!<�ÓI�����I�u�W�F�N�g�B
	CPhysicsGhostObject m_ghostObject;
	int m_number;
	float m_sdegree;
	CFont m_font;
};
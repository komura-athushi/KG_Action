#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"

class StageKanri;
class Background : public IGameObject
{
public:
	//�����o�֐��B
	Background();
	~Background();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,000.0f,0.0f };			//���W�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	StageKanri* m_stagekanri;
};


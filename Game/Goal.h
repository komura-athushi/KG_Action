#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Goal : public IGameObject
{
public:
	//メンバ関数。
	Goal();
	~Goal();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//座標。
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;			//!<静的物理オブジェクト。
};
#pragma once
#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Sword : public IGameObject
{
public:
	//メンバ関数。
	Sword();
	~Sword();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転速度を設定
	void SetSdegree(const float& sdegree)
	{
		m_sdegree = sdegree;
	}
	//ゴーストを取得
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 0.0f,50.0f,0.0f };			//座標。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<静的物理オブジェクト。
	CVector3 m_scale = { 5.0f,5.0f,7.5f };
	CPhysicsGhostObject m_ghostObject;
	float m_degree = 0.0f;
	float m_sdegree = 1.9f;
	CVector3 m_tyusin = CVector3::Zero;
	float const m_r = 200.0f;
};

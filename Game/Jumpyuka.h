#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
//上に乗るとY軸にキャラが飛ぶ
class Jumpyuka : public IGameObject
{
public:
	//メンバ関数。
	Jumpyuka();
	~Jumpyuka();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//ゴーストを取得
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 300.0f,50.0f,0.0f };			//座標。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;			//!<静的物理オブジェクト。
	CPhysicsGhostObject m_ghostObject;
};
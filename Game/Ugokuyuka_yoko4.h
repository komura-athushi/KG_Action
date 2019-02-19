#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_yoko4 : public IGameObject
{
public:
	//メンバ関数。
	Ugokuyuka_yoko4();
	~Ugokuyuka_yoko4();
	bool Start();
	void Update();
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//座標。
	CVector3 m_protposition = m_position;
	CVector3 m_lastframposition = CVector3::Zero;
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	CVector3 m_movespeed = { 0.5f,0.0f,0.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;					//!<静的物理オブジェクト。
	CPhysicsGhostObject m_ghostObject;
};
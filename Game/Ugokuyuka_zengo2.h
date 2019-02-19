#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_zengo2 : public IGameObject
{
public:
	//メンバ関数。
	Ugokuyuka_zengo2();
	~Ugokuyuka_zengo2();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos) 
	{
		m_position = pos;
	}
	//初期座標を設定
	void SetProtPosition(const CVector3& pos) 
	{
		m_protposition = pos;
	}
	//移動速度を設定
	void SetMovespeed(const CVector3& speed) 
	{
		m_movespeed = speed;
	}
	//1フレーム前の座標を取得
	CVector3 GetLastFramPosition() const
	{
		return m_lastframposition;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//ゴーストを取得
	CPhysicsGhostObject* GetGhostObject() 
	{
		return &m_ghostObject;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,0.0f };			//座標。
	CVector3 m_lastframposition = CVector3::Zero;
	CVector3 m_protposition = m_position;
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	CVector3 m_movespeed = { 0.0f,0.0f,3.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<静的物理オブジェクト。
	CPhysicsGhostObject m_ghostObject;
	int m_timer = 0;
	const float m_movespeedZ = 7.5f / 0.03f;
};
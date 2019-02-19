#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Meteo : public IGameObject
{
public:
	//メンバ関数。
	Meteo();
	~Meteo();
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
	//メンバ変数。
	CVector3 m_position = CVector3::Zero;			//座標。
	CVector3 m_movespeed = CVector3::Zero; //移動速度。 												
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;						//タイマー。									//弾の大きさ
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	int m_deletetime;
	CPhysicsGhostObject m_ghostObject;
};
#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class SphereRing;
class Boss;
class SphereRing_Big : public IGameObject
{
public:
	//メンバ関数。
	SphereRing_Big();
	~SphereRing_Big();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//移動速度を設定
	void SetMovespeed(const CVector3& speed)
	{
		m_movespeed = speed;
	}
private:
	//メンバ変数。
	CVector3 m_position = CVector3::Zero;			//座標。
	CVector3 m_movespeed = CVector3::Zero; //移動速度。										
	prefab::CEffect* m_effect = nullptr;
	int m_timer = 0;						//タイマー。
	int m_sphereringtimer = 0;
	int m_sphereringcount = 0;
	CVector3 m_scale = { 2.5f,2.5f,2.5f };
	SphereRing* m_spherering;
	Boss* m_boss;
};
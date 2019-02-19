#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class SphereRing : public IGameObject
{
public:
	//メンバ関数。
	SphereRing();
	~SphereRing();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//移動の目標の座標を設定
	void SetGoalPosition(const CVector3& goalpos)
	{
		m_goalposition = goalpos;
	}
	//ゴーストを取得
	CPhysicsGhostObject* GetGhostObject()
	{
		return &m_ghostObject;
	}
private:
	//メンバ変数。
	CVector3 m_position = CVector3::Zero;			//座標。
	CVector3 m_protposition = CVector3::Zero;
	//ボスの座標から移動した時の停止する場所
	CVector3 m_goalposition = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	CPhysicsGhostObject m_ghostObject;
	int m_timer = 0;						//タイマー。
	//m_position.xを＋するか-するか										
	bool m_plusXZ = true;
	CVector3 m_scale;
	// 二次関数の各定数 y=-a(x-b)^2+c m_aはyの移動速度 m_cはyの最大値 m_bはyが最大値の時の-xの値
	float m_a;
	float m_b,m_b2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	float m_c=300.0f;
	//xおよびzの移動速度
	float m_smovespeedX;
	float m_smovespeedZ;
	bool m_move = true;
};
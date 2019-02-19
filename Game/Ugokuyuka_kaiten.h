#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Ugokuyuka_kaiten : public IGameObject
{
public:
	//メンバ関数。
	Ugokuyuka_kaiten();
	~Ugokuyuka_kaiten();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_tyusin = pos;
	}
	//移動速度を設定
	void SetSdegree(const float& sdegree)
	{
		m_sdegree = sdegree;
	}
	//ナンバーを設定
	void SetNumber(const int& number)
	{
		m_number = number;
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
	//void PostRender(CRenderContext& renderContext);
	CVector3 m_tyusin = CVector3::Zero;
	float m_degree = 0.0f;
	//半径
	float m_r = 400.0f;
	CVector3 m_position = m_tyusin;			//座標。
	CVector3 m_scale = { 0.03f,0.03f,0.03f };
	CVector3 m_lastframposition = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;					//!<静的物理オブジェクト。
	CPhysicsGhostObject m_ghostObject;
	int m_number;
	float m_sdegree;
	CFont m_font;
};
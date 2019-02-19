#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"

class StageKanri;
class Background : public IGameObject
{
public:
	//メンバ関数。
	Background();
	~Background();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,000.0f,0.0f };			//座標。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<静的物理オブジェクト。
	StageKanri* m_stagekanri;
};


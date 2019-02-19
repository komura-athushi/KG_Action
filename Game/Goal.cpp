#include "stdafx.h"
#include "Goal.h"

Goal::Goal()
{
}

Goal::~Goal()
{
	DeleteGO(m_skinModelRender);
}
bool Goal::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Goal.cmo");
	m_position *= 0.03f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, m_position, CQuaternion::Identity, m_scale);
	
	return true;
}
void Goal::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
}

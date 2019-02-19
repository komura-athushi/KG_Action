#include "stdafx.h"
#include "Background.h"
#include "StageKanri.h"
Background::Background()
{
}

Background::~Background()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_stagekanri = FindGO<StageKanri>("StageKanri");
	CVector3 scale;
	switch (m_stagekanri->GetStageNumber()) {
	case 1:
		m_skinModelRender->Init(L"modelData/Background1.cmo");
		m_skinModelRender->SetPosition(m_position);
		scale = { 0.03f,0.03f,0.03f };
		m_skinModelRender->SetScale(scale);
		m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity, scale);
		break;
	case 2:
		m_skinModelRender->Init(L"modelData/Background2.cmo");
		m_skinModelRender->SetPosition(m_position);
		m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity, CVector3::One);
		break;
	case 3:
		m_skinModelRender->Init(L"modelData/Background3.cmo");
		m_skinModelRender->SetPosition(m_position);
		scale = { 0.008f,0.03f,0.008f };
		m_skinModelRender->SetScale(scale);
		m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity,scale);
	}
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
void Background::Update()
{
	
}

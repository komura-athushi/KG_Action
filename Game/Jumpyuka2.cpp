#include "stdafx.h"
#include "Jumpyuka2.h"

Jumpyuka2::Jumpyuka2()
{
}


Jumpyuka2::~Jumpyuka2()
{
	DeleteGO(m_skinModelRender);
}
bool Jumpyuka2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Jumpyuka2.cmo");
	m_skinModelRender->SetPosition(m_position);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 175.0f,30.0f,145.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 170.0f, 31.0f, 140.0f }	//第三引数はボックスのサイズ。
	);

	return true;
}
void Jumpyuka2::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
}

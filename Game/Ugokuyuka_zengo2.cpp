#include "stdafx.h"
#include "Ugokuyuka_zengo2.h"

Ugokuyuka_zengo2::Ugokuyuka_zengo2()
{
}


Ugokuyuka_zengo2::~Ugokuyuka_zengo2()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_zengo2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_zengo.cmo");
	m_position *= 0.03f;
	m_protposition *= 0.03f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 380.0f,100.0f,440.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 385.0f, 101.0f, 445.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}
void Ugokuyuka_zengo2::Update()
{
	m_lastframposition = m_position;
	
	if (m_timer >= 20) {
		m_position.z += m_movespeed.z*GameTime().GetFrameDeltaTime();
	}
	if (m_position.z > m_protposition.z + 500.0f) {
		m_position.z = m_protposition.z + 500.0f;
		m_movespeed.z = -m_movespeedZ;
		m_timer = 0;
	}
	else if (m_position.z < m_protposition.z - 500.0f) {
		m_position.z = m_protposition.z - 500.0f;
		m_movespeed.z = m_movespeedZ;
		m_timer = 0;
	}
	m_timer++;
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

#include "stdafx.h"
#include "Ugokuyuka_yoko2.h"

Ugokuyuka_yoko2::Ugokuyuka_yoko2()
{
}

Ugokuyuka_yoko2::~Ugokuyuka_yoko2()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_yoko2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_yoko2.cmo");
	m_position *= 0.03f;
	m_protposition *= 0.03f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 450.0f,100.0f,520.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 445.0f, 101.0f, 515.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}
void Ugokuyuka_yoko2::Update()
{
	m_lastframposition = m_position;
	
	if (m_timer >= 20) {
		m_position.x += m_movespeed.x*GameTime().GetFrameDeltaTime();
	}
	if (m_position.x > m_protposition.x + 500.0f) {
		m_position.x = m_protposition.x + 500.0f;
		m_movespeed.x = -m_movespeedX;
		m_timer = 0;
	}
	else if (m_position.x < m_protposition.x - 500.0f) {
		m_position.x = m_protposition.x - 500.0f;
		m_movespeed.x = m_movespeedX;
		m_timer = 0;
	}
	m_timer++;
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

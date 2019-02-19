#include "stdafx.h"
#include "Ugokuyuka_yoko.h"

Ugokuyuka_yoko::Ugokuyuka_yoko()
{
}


Ugokuyuka_yoko::~Ugokuyuka_yoko()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_yoko::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_yoko.cmo");
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
		{ 375.0f, 101.0f, 435.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}
void Ugokuyuka_yoko::Update()
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
	else if (m_position.x < m_protposition.x - 400.0f) {
		m_position.x = m_protposition.x - 400.0f;
		m_movespeed.x = m_movespeedX;
		m_timer = 0;
	}
	m_timer++;
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

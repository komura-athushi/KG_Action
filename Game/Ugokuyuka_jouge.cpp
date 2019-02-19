#include "stdafx.h"
#include "Ugokuyuka_jouge.h"

Ugokuyuka_jouge::Ugokuyuka_jouge()
{
}


Ugokuyuka_jouge::~Ugokuyuka_jouge()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_jouge::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_jouge.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 340.0f,100.0f,400.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 341.0f, 101.0f, 401.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}
void Ugokuyuka_jouge::Update()
{
	m_lastframposition = m_position;
	if (m_position.y >= m_protposition.y + 200.0f) {
		m_position.y = 200.0f;
		m_movespeed.y = -2.0f;
	}
	else if (m_position.y <= m_protposition.y - 200.0f) {
		m_position.y = -200.0f;
		m_movespeed.y = 2.0f;
	}
	m_position.y += m_movespeed.y;
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

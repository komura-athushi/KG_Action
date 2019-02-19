#include "stdafx.h"
#include "Ugokuyuka_yoko4.h"

Ugokuyuka_yoko4::Ugokuyuka_yoko4()
{
}


Ugokuyuka_yoko4::~Ugokuyuka_yoko4()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_yoko4::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_yoko4.cmo");
	m_position *= 0.03f;
	m_protposition *= 0.03f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 500.0f,430.0f,1760.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 495.0f, 431.0f, 1755.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}
void Ugokuyuka_yoko4::Update()
{
	m_lastframposition = m_position;
	if (m_position.x >= m_protposition.x + 200.0f) {
		m_position.x = m_protposition.x + 200.0f;
		m_movespeed.x = -0.7f;
	}
	else if (m_position.x <= m_protposition.x - 200.0f) {
		m_position.x = m_protposition.x - 200.0f;
		m_movespeed.x = 0.7f;
	}
	m_position.x += m_movespeed.x;
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

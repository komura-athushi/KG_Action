#include "stdafx.h" 
#include "Circle2.h"
#include "Player.h"
#include "Boss.h"
#include "Meteo.h"
Circle2::Circle2()
{
}
Circle2::~Circle2()
{
	//DeleteGO(m_effect);
}
bool Circle2::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/Circle2.efk");
	m_effect->SetScale(m_scale);
	m_boss = FindGO<Boss>("Boss");
	return true;
}
void Circle2::Update()
{
	m_effect->SetPosition(m_position);
	if (m_timer == 205) {
		m_meteo = NewGO<Meteo>(0, "Meteo");
		CVector3 pos = m_position;
		pos.y = 500.0f;
		m_meteo->SetPosition(pos);
		DeleteGO(this);
	}
	m_timer++;
}
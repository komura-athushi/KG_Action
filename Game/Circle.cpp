#include "stdafx.h" 
#include "Circle.h"
#include "Player.h"
#include "Boss.h"
#include "Pyramid.h"
Circle::Circle()
{
}
Circle::~Circle()
{
	//DeleteGO(m_effect);
}
bool Circle::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/Circle.efk");
	m_effect->SetScale(m_scale);
	m_player = FindGO<Player>("Player");
	m_effect->SetPosition(m_player->GetPosition());
	m_boss = FindGO<Boss>("Boss");
	return true;
}
void Circle::Update()
{
	CVector3 Pos = m_player->GetPosition();
	Pos.y = 1.0f;
	m_effect->SetPosition(Pos);
	if (m_timer == 205) {
		m_pyramid = NewGO<Pyramid>(0, "Pyramid");
		Pos.y = 700.0f;
		m_pyramid->SetPosition(Pos);
		DeleteGO(this);
	}
	m_timer++;
}
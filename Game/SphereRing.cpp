#include "stdafx.h" 
#include "SphereRing.h"
#include <math.h>
SphereRing::SphereRing()
{
}
SphereRing::~SphereRing()
{
	DeleteGO(m_effect);
}
bool SphereRing::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/SphereRing.efk");
	m_effect->SetPosition(m_position);
	m_scale = { 1.5f,1.5f,1.5f };
	m_effect->SetScale(m_scale);
	m_protposition = m_position;
	//ここから二次関数のそれぞれの定数を求めていく y=a((x+z)-b)^2+c
	m_b = m_goalposition.x/2;
	m_b2 = m_goalposition.z/2;
	m_a = (m_c - m_protposition.y) / pow((m_b + m_b2), 2.0f);
	m_smovespeedX = m_b / 50.0f;
	m_smovespeedZ = m_b2 / 50.0f;
	m_ghostObject.CreateSphere(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		60.0f
	);
	return true;
}
void SphereRing::Update()
{
	if (m_timer == 80) {
		DeleteGO(this);
	}
	if (m_move) {
		m_position.x += m_smovespeedX;
		m_position.z += m_smovespeedZ;
		//二次関数の式を使っているんだゾ y=-a(x-b)^2+c xの2乗→→#include <math.h>  pow(x,2.0f)
		m_position.y = -m_a * pow((m_position.x + m_position.z - (m_b + m_b2)), 2.0f) + m_c;
	}
	if (m_position.y<m_protposition.y) {
		m_move = false;
		//タイマーを加算する。
		m_timer++;
	}
	m_effect->SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}
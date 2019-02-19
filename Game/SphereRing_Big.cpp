#include "stdafx.h" 
#include "SphereRing_Big.h"
#include "SphereRing.h"
#include "Boss.h"
SphereRing_Big::SphereRing_Big()
{
}
SphereRing_Big::~SphereRing_Big()
{
	DeleteGO(m_effect);

}
bool SphereRing_Big::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/SphereRing.efk");
	m_effect->SetPosition(m_position);
	m_effect->SetScale(m_scale);
	m_movespeed.y = -10.0f;
	m_boss = FindGO<Boss>("Boss");
	return true;
}
void SphereRing_Big::Update()
{
	if (m_position.y <= -150.0f) {
		if (m_sphereringtimer == 15) {
			m_spherering = NewGO<SphereRing>(0, "SphereRing");
			CVector3 pos = m_boss->GetPosition();
			pos.y = 70.0f;
			m_spherering->SetPosition(pos);
			CVector3 Pos;
			Pos.y = 300.0f;
			//x,yÀ•W‚Í-930`-350,350`930‚ÌŠÔ‚É—ˆ‚é‚æ‚¤‚É‚·‚é
			if (rand() % 101 > 50) {
				Pos.z = 350.0f + rand() % 809 * 0.65f;
			}
			else {
				Pos.z = -350.0f - rand() % 809 * 0.65f;
			}
			if (rand() % 211 > 105) {
				Pos.x = 350.0f + rand() % 317 * 1.78f;
			}
			else {
				Pos.x = -350.0f - rand() % 317 * 1.78f;
			}
			if (rand() % 4 == 0) {
				if (rand() % 9 > 4) {
					Pos.x = 0.0f;
				}
				else {
					Pos.z = 0.0f;
				}
			}
			m_spherering->SetGoalPosition(Pos);
			m_sphereringcount++;
			m_sphereringtimer = 0;
		}
		m_sphereringtimer++;
		if (m_sphereringcount == 20) {
			DeleteGO(this);
		}
	}
	else {
		m_position += m_movespeed;
		m_effect->SetPosition(m_position);
	}
}
#include "stdafx.h" 
#include "BossLife.h"
#include "Boss.h"

BossLife::BossLife()
{
}
BossLife::~BossLife()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriteRender2);
}
bool BossLife::Start()
{
	//CSpriteRenderのインスタンスを作成。  
	m_spriteRender2 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender2->Init(L"sprite/HPgage_b.dds", m_side2*2, m_length2);
	m_spriteRender2->SetPosition(m_position);
	m_spriteRender->Init(L"sprite/HPgage_Boss.dds", m_side*2, m_length);
	m_spriteRender->SetPosition(m_position);
	m_boss = FindGO<Boss>("Boss");
	return true;
}
void BossLife::Update()
{
	float hpRate = (float)m_boss->GetLife() / m_boss->GetProtlife();
	float offsetX = (hpRate - 1.0f)*m_side / 2*2;
	m_position.x = m_protposition.x + offsetX;
	m_spriteRender->SetPosition(m_position);
	//Initk,関数 tkSpriteRender.hおよびcppに追加した (画像の横の長さ,縦の長さ)
	m_spriteRender->Initk(m_side*hpRate*2, m_length);
}
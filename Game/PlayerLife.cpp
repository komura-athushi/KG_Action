#include "stdafx.h" 
#include "PlayerLife.h"
#include "Player.h"

PlayerLife::PlayerLife()
{
}
PlayerLife::~PlayerLife()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriteRender2);
}
bool PlayerLife::Start()
{
	//CSpriteRenderのインスタンスを作成。  
	m_spriteRender2 = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender2->Init(L"sprite/HPgage_b.dds", m_side2, m_length2);
	m_spriteRender2->SetPosition(m_position);
	m_spriteRender->Init(L"sprite/HPgage.dds", m_side, m_length);
	m_spriteRender->SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	return true;
}
void PlayerLife::Update()
{
	float hpRate = (float)m_player->GetLife() / m_player->GetProtLife();
	float offsetX = (hpRate - 1.0f)*m_side / 2;
	m_position.x = m_protposition.x + offsetX;
	m_spriteRender->SetPosition(m_position);
	//Initk,関数 tkSpriteRender.hおよびcppに追加した (画像の横の長さ,縦の長さ)
	m_spriteRender->Initk(m_side*hpRate, m_length);
}
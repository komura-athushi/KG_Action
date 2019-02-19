#include "stdafx.h" 
#include "EnemyBullet.h"
EnemyBullet::EnemyBullet()
{
}
EnemyBullet::~EnemyBullet()
{
	DeleteGO(m_skinModelRender);
}
bool EnemyBullet::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/EnemyBullet.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	return true;
}
void EnemyBullet::Update()
{
	if (m_timer == m_deletetime) {
		DeleteGO(this);
	}
	m_position += m_movespeed;
	m_skinModelRender->SetPosition(m_position);
	m_timer++;
}
	
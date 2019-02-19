#include "stdafx.h" 
#include "Pyramid.h"
Pyramid::Pyramid()
{
}
Pyramid::~Pyramid()
{
	DeleteGO(m_skinModelRender);
}
bool Pyramid::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Pyramid.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_movespeed.y = -20.0f;
	return true;
}
void Pyramid::Update()
{
	if (m_position.y <= -400.0f) {
	     DeleteGO(this);
	}
	m_position += m_movespeed;
	m_skinModelRender->SetPosition(m_position);
	m_timer++;
}
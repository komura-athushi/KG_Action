#include "stdafx.h" 
#include "Meteo.h"
Meteo::Meteo()
{
}
Meteo::~Meteo()
{
	DeleteGO(m_skinModelRender);
}
bool Meteo::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Meteo.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_movespeed.y = -25.0f;
	m_ghostObject.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 180.0f, 300.0f, 180.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	return true;
}
void Meteo::Update()
{
	if (m_position.y <= -300.0f) {
		DeleteGO(this);
	}
	m_position += m_movespeed;
	m_skinModelRender->SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
	m_timer++;
}
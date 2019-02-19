#include "stdafx.h" 
#include "PlayerBullet.h"
PlayerBullet::PlayerBullet()
{
}
PlayerBullet::~PlayerBullet()
{
	DeleteGO(m_effect);
}
bool PlayerBullet::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/RedSphere.efk");
	m_scale = { 1.0f,1.0f,1.0f };
	m_effect->SetScale(m_scale);
	return true;
}
void PlayerBullet::Update()
{
	//�e�ۂ��ړ�������B  
	m_position += m_movespeed;
	m_effect->SetPosition(m_position);
	if (m_timer == 9) {
		DeleteGO(this);
	}
	//�^�C�}�[�����Z����B
	m_timer++;
}
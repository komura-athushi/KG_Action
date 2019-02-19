#include "stdafx.h"
#include "Ugokuyuka_yoko3.h"

Ugokuyuka_yoko3::Ugokuyuka_yoko3()
{
}


Ugokuyuka_yoko3::~Ugokuyuka_yoko3()
{
	DeleteGO(m_skinModelRender);
}
bool Ugokuyuka_yoko3::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_yoko3.cmo");
	m_position *= 0.03f;
	m_protposition *= 0.03f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 450.0f,500.0f,530.0f });
	m_ghostObject.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 455.0f, 501.0f, 535.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	m_movespeedX = 2.2 + 1.2f*m_number;
	m_movespeedX /= 0.03f;
	m_movespeed.x = m_movespeedX;
	return true;
}
void Ugokuyuka_yoko3::Update()
{
	m_lastframposition = m_position;
	if (m_position.x >= m_protposition.x + 200.0f) {
		m_position.x = m_protposition.x + 200.0f;
		m_movespeed.x = -m_movespeedX;
	}
	else if (m_position.x <= m_protposition.x - 200.0f) {
		m_position.x = m_protposition.x - 200.0f;
		m_movespeed.x = m_movespeedX;
	}
	m_position.x += m_movespeed.x*GameTime().GetFrameDeltaTime();
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

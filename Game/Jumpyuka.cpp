#include "stdafx.h"
#include "Jumpyuka.h"

Jumpyuka::Jumpyuka()
{
}


Jumpyuka::~Jumpyuka()
{
	DeleteGO(m_skinModelRender);
}
bool Jumpyuka::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Jumpyuka.cmo");
	m_skinModelRender->SetPosition(m_position);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 290.0f,30.0f,160.0f });
	m_ghostObject.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 280.0f, 31.0f, 150.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	return true;
}
void Jumpyuka::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
}

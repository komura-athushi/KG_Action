#include "stdafx.h"
#include "Sword.h"
#define _USE_MATH_DEFINES
#include <math.h>
Sword::Sword()
{
}

Sword::~Sword()
{
	DeleteGO(m_skinModelRender);
}
bool Sword::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/DoubleSword.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//�ÓI�����I�u�W�F�N�g���쐬�B
	//m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 100.0f,40.0f,2000.0f });
	m_ghostObject.CreateBox(
		m_position,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 100.0f, 40.0f, 2000.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
void Sword::Update()
{
	float radian = m_degree * M_PI / 180.0f;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, radian/2);
	m_degree+=m_sdegree;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
	m_ghostObject.SetPosition(m_position);
	m_ghostObject.SetRotation(qRot);

}

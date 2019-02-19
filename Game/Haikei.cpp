#include "stdafx.h"
#include "Haikei.h"

Haikei::Haikei()
{
}


Haikei::~Haikei()
{
	DeleteGO(m_skinModelRender);
}
bool Haikei::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Haikei.cmo");
	m_skinModelRender->SetPosition(CVector3::Zero);
	CVector3 scale = { 0.025,0.025,0.030 };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
void Haikei::Update()
{

}

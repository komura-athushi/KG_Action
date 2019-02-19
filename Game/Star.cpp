#include "stdafx.h" 
#include "Star.h"
#include "Player.h"
#include "Game.h"
#include "StageKanri.h"
Star::Star()
{
}
Star::~Star()
{
	DeleteGO(m_skinModelRender);
}
bool Star::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Star.cmo");
	m_stagekanri = FindGO<StageKanri>("StageKanri");
	if (m_stagekanri->GetStageNumber() == 1) {
		m_position *= 0.03f;
	}
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_player=FindGO<Player>("Player");
	return true;
}
void Star::Update()
{
	if (!m_isGet) {
		CVector3 dist = m_player->GetPosition() - m_position;
		if (dist.Length() < 150.0f) {
			m_jumpspeed = 700.0f;
			m_isGet = true;
			m_jumStartPosY = m_position.y;
			m_player->Stop();
		}
	}
	else {
		m_position.y += m_jumpspeed * GameTime().GetFrameDeltaTime();
		m_jumpspeed -= 980.0f * GameTime().GetFrameDeltaTime();
		if (m_jumStartPosY > m_position.y) {
			FindGO<Game>("Game")->Gameclear();
			m_stagekanri->StageClear();
			DeleteGO(this);
		}
	}
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY,m_kaiten);
	m_skinModelRender->SetRotation(qRot);
	m_skinModelRender->SetPosition(m_position);
	m_kaiten += 0.05f;
}
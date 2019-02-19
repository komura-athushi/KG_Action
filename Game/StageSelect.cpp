#include "stdafx.h" 
#include "StageSelect.h"
#include "Fade.h"
#include "StageKanri.h"
#include "Title.h"
#include "Game.h"
#include "Sound.h"
StageSelect::StageSelect()
{
}
StageSelect::~StageSelect()
{
	DeleteGO(m_spriteRender);
	for (int i = 0; i < 5; i++) {
		DeleteGO(m_stagepointa[i]);
	}
	DeleteGO(m_cursor);
}
bool StageSelect::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/StageSelect.dds", 1280.0f, 720.0f);
	m_stagekanri = FindGO<StageKanri>("StageKanri");
	Pointa();
	m_cursor = NewGO<prefab::CSpriteRender>(0);
	m_cursor->Init(L"sprite/Cursor.dds", 150.0f, 130.0f);
	m_cursorposition = { -580, -200, 0 };
	m_cursor->SetPosition(m_cursorposition);
	Sound* m_sound = FindGO<Sound>("Sound");
	m_sound->SetBGM(0);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void StageSelect::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_gamein) {
				NewGO<Game>(0, "Game");
				DeleteGO(this);
			}
			else {
				NewGO<TitleScene>(0, "TitleScene");
				DeleteGO(this);
			}

		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonB)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			m_stagekanri->SetStageNumber(m_state+1);
			m_gamein = true;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
		}
		else if (Pad(0).IsTrigger(enButtonA)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Cancel.wav");
			ss->Play(false);
		}
		Cursor();
	}
}
void StageSelect::Pointa()
{
	for (int i = 0; i < m_stagekanri->GetStage(); i++) {
		//もしクリアしていれば
		if (m_stagekanri->GetClear(i)) {
			m_stagepointa[i] = NewGO<prefab::CSpriteRender>(0);
			m_stagepointa[i]->Init(L"sprite/Stagepointa_clear.dds", 200.0f, 150.0f);
			CVector3 m_position = { (float)i * 220.0f - 500.0f, -200, 0 };
			m_stagepointa[i]->SetPosition(m_position);
		}
		//もしクリアしていなければ
		else {
			m_stagepointa[i] = NewGO<prefab::CSpriteRender>(0);
			m_stagepointa[i]->Init(L"sprite/Stagepointa.dds", 200.0f, 150.0f);
			CVector3 m_position = { (float)i * 220.0f - 500.0f, -200, 0 };
			m_stagepointa[i]->SetPosition(m_position);
		}
	}

}
void StageSelect::Cursor()
{
	if (Pad(0).IsTrigger(enButtonRight)) {
		switch (m_state) {
		case STAGE1:
			m_cursorposition.x += 220.0f;
			m_state = STAGE2;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case STAGE2:
			m_cursorposition.x += 220.0f;
			m_state = STAGE3;
			prefab::CSoundSource* sss;
			sss = NewGO<prefab::CSoundSource>(0);
			sss->Init(L"sound/Enter.wav");
			sss->Play(false);
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)) {
		switch (m_state) {
		case STAGE2:
			m_cursorposition.x -= 220.0f;
			m_state = STAGE1;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case STAGE3:
			m_cursorposition.x -= 220.0f;
			m_state = STAGE2;
			prefab::CSoundSource* sss;
			sss = NewGO<prefab::CSoundSource>(0);
			sss->Init(L"sound/Enter.wav");
			sss->Play(false);
			break;
		}
	}
	m_cursor->SetPosition(m_cursorposition);
}
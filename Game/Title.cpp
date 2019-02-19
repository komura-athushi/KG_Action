#include "stdafx.h" 
#include "Title.h" 
#include "StageSelect.h"
#include "Fade.h"
#include "Manual.h"
#include "Config.h"
#include "Credit.h"
TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_cursor);
}
bool TitleScene::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title.dds", 1280.0f, 720.0f);
	m_cursor = NewGO<prefab::CSpriteRender>(0);
	m_cursor->Init(L"sprite/Cursor_Title.dds", 1050.0f, 550.0f);
	m_cursor->SetPosition(m_cursorposition);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void TitleScene::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_state==STAGESELECT) {
				NewGO<StageSelect>(0, "StageSelect");
				DeleteGO(this);
			}
			else if (m_state == CONFIG) {
				NewGO<Config>(0, "Config");
				DeleteGO(this);
			}
			else if (m_state==MANUAL) {
				NewGO<Manual>(0, "Manual");
				DeleteGO(this);
			}
			else if (m_state == CREDIT) {
				NewGO<Credit>(0, "Credit");
				DeleteGO(this);
			}
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonB)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
		}
		Cursor();
	}
}
void TitleScene::Cursor()
{
	if (Pad(0).IsTrigger(enButtonUp)) {
		switch (m_state) {
		case CONFIG:
			m_cursorposition.y += 97.0f;
			m_state = STAGESELECT;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case MANUAL:
			m_cursorposition.y += 97.0f;
			m_state = CONFIG;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case CREDIT:
			m_cursorposition.y += 97.0f;
			m_state = MANUAL;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonDown)) {
		switch (m_state) {
		case STAGESELECT:
			m_cursorposition.y -= 97.0f;
			m_state = CONFIG;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case CONFIG:
			m_cursorposition.y -= 97.0f;
			m_state = MANUAL;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case MANUAL:
			m_cursorposition.y -= 97.0f;
			m_state = CREDIT;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		}
	}
	m_cursor->SetPosition(m_cursorposition);
}
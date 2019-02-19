#include "stdafx.h" 
#include "Config.h" 
#include "Fade.h"
#include "Title.h"
#include "PlayerStatus.h"
Config::Config()
{
}
Config::~Config()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_cursor);
}
bool Config::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/COnfig.dds", 1280.0f, 720.0f);
	m_cursor = NewGO<prefab::CSpriteRender>(0);
	m_cursor->Init(L"sprite/Cursor_Title.dds", 1050.0f, 550.0f);
	m_cursor->SetPosition(m_cursorposition);
	m_fade = FindGO<Fade>("Fade");
	m_playerstatus = FindGO<PlayerStatus>("PlayerStatus");
	m_fade->StartFadeIn();
	return true;
}
void Config::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<TitleScene>(0, "TitleScene");
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonA)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Cancel.wav");
			ss->Play(false);
		}
		else if (Pad(0).IsTrigger(enButtonB)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			switch (m_state) {
			case EASY:
				m_playerstatus->SetHeart(10);
					m_playerstatus->SetLife(20);
				break;
			case NORMAL:
				m_playerstatus->SetHeart(5);
				m_playerstatus->SetLife(10);
				break;
			case HARD:
				m_playerstatus->SetHeart(2);
				m_playerstatus->SetLife(5);
				break;
			}
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
		}
		Cursor();
	}
}

void Config::Cursor()
{
	if (Pad(0).IsTrigger(enButtonUp)) {
		switch (m_state) {
		case NORMAL:
			m_cursorposition.y += 103.0f;
			m_state = EASY;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case HARD:
			m_cursorposition.y += 103.0f;
			m_state = NORMAL;
			prefab::CSoundSource* sss;
			sss = NewGO<prefab::CSoundSource>(0);
			sss->Init(L"sound/Enter.wav");
			sss->Play(false);
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonDown)) {
		switch (m_state) {
		case EASY:
			m_cursorposition.y -= 103.0f;
			m_state = NORMAL;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
			break;
		case NORMAL:
			m_cursorposition.y -= 103.0f;
			m_state = HARD;
			prefab::CSoundSource* sss;
			sss = NewGO<prefab::CSoundSource>(0);
			sss->Init(L"sound/Enter.wav");
			sss->Play(false);
			break;
		}
	}
	m_cursor->SetPosition(m_cursorposition);
}
#include "stdafx.h" 
#include "GameOver.h" 
#include "StageSelect.h"
#include "Fade.h"
#include "Title.h"
#include "Sound.h"
GameOver::GameOver()
{
}
GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}
bool GameOver::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/GameOver.dds", 1280.0f, 720.0f);
	Sound* m_sound = FindGO<Sound>("Sound");
	m_sound->SetBGM(0);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void GameOver::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<StageSelect>(0, "StageSelect");
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonB)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Enter.wav");
			ss->Play(false);
		}
	}
}
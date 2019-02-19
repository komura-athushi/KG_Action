#include "stdafx.h" 
#include "Manual.h" 
#include "Fade.h"
#include "Title.h"
Manual::Manual()
{
}
Manual::~Manual()
{
	DeleteGO(m_spriteRender);
}
bool Manual::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Manual.dds", 1280.0f, 720.0f);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Manual::Update()
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
	}
}
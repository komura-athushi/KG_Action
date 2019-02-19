#include "stdafx.h"
#include "Sound.h"
Sound::Sound()
{
}
Sound::~Sound()
{
}
bool Sound::Start()
{
	m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);	//BGM用のサウンドソース。
	m_bgmSoundSource->Init(L"sound/Title.wav");
	m_bgmSoundSource->Play(true);
	return true;
}
void Sound::Update()
{
	State();
}

void Sound::State()
{
	if (m_state1 != m_state2) {
		DeleteGO(m_bgmSoundSource);
		switch (m_state2) {
		case 0:
			m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);
			m_bgmSoundSource->Init(L"sound/Title.wav");
			m_bgmSoundSource->Play(true);
			break;
		case 1:
			m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);
			m_bgmSoundSource->Init(L"sound/STAGE1.wav");
			m_bgmSoundSource->Play(true);
			break;
		case 2:
			m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);
			m_bgmSoundSource->Init(L"sound/STAGE2.wav");
			m_bgmSoundSource->Play(true);
			break;
		case 3:
			m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);
			m_bgmSoundSource->Init(L"sound/STAGE3.wav");
			m_bgmSoundSource->Play(true);
			break;
		}
		m_state1 = m_state2;
	}
}
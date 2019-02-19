#pragma once
class Fade;
class Manual : public IGameObject {
public:
	Manual();
	~Manual();
	bool Start();
	void Update();
private:
	//スプライトレンダラー。  
	prefab::CSpriteRender* m_spriteRender = nullptr;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};

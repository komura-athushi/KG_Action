#pragma once
class Fade;
class TitleScene : public IGameObject {
public:
	TitleScene();
	~TitleScene();
	bool Start();
	void Update();
	void Cursor();
private:
	//スプライトレンダラー。  
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_cursor = nullptr;
	prefab::CSoundSource* ss;
	CVector3 m_cursorposition = { 100.0f,-37,0.0f };
	enum State {
	    STAGESELECT,
		CONFIG,
		MANUAL,
		CREDIT,
	};
	State m_state = STAGESELECT;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};

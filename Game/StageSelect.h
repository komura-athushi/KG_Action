#pragma once
class Fade;
class StageKanri;
class StageSelect : public IGameObject {
public:
	StageSelect();
	~StageSelect();
	bool Start();
	void Update();
	//ステージのポインタ生成
	void Pointa();
	//カーソルの生成
	void Cursor();
private:
	//スプライトレンダラー。  
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_stagepointa[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	prefab::CSpriteRender* m_cursor = nullptr;
	CVector3 m_cursorposition;
	enum STAGE {
		STAGE1,
		STAGE2,
		STAGE3,
	};
	STAGE m_state = STAGE1;
	bool m_gamein = false;
	StageKanri * m_stagekanri;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};
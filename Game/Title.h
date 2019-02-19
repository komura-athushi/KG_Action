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
	//�X�v���C�g�����_���[�B  
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
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};

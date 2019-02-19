#pragma once
class Fade;
class PlayerStatus;
class Config : public IGameObject {
public:
	Config();
	~Config();
	bool Start();
	void Update();
	void Cursor();
private:
	//�X�v���C�g�����_���[�B  
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_cursor = nullptr;
	CVector3 m_cursorposition = { -270.0f,50,0.0f };
	enum Level
	{
		EASY,
		NORMAL,
		HARD,
	};
	Level m_state = EASY;
	PlayerStatus* m_playerstatus;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};
#pragma once
class Fade;
class Manual : public IGameObject {
public:
	Manual();
	~Manual();
	bool Start();
	void Update();
private:
	//�X�v���C�g�����_���[�B  
	prefab::CSpriteRender* m_spriteRender = nullptr;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};

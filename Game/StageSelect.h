#pragma once
class Fade;
class StageKanri;
class StageSelect : public IGameObject {
public:
	StageSelect();
	~StageSelect();
	bool Start();
	void Update();
	//�X�e�[�W�̃|�C���^����
	void Pointa();
	//�J�[�\���̐���
	void Cursor();
private:
	//�X�v���C�g�����_���[�B  
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
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
};
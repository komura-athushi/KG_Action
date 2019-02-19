#pragma once
class Player;
class PlayerLife : public IGameObject {
public:
	PlayerLife();
	~PlayerLife();
	//IGameObject��Start�֐����I�[�o�[���C�h����B  
	bool Start();
	//IGameObject��Update�֐����I�[�o�[���C�h����B  
	void Update();
private:
	//�X�v���C�g�����_���[�B  
	prefab::CSpriteRender* m_spriteRender = nullptr;  
	prefab::CSpriteRender* m_spriteRender2 = nullptr;
	//���C�t�\���̏����ʒu
	CVector3 m_protposition = { -400,-300,0 };
	//���C�t�\���̍��W
	CVector3 m_position = m_protposition;
	//���C�t�\���̏����̉��̒���
	float m_side = 384.0f;
	//���C�t�\���̏����̏c�̒���
	float m_length = 64.0f;
	//���C�t�̌��̂�̒���
	float m_side2 = 512.0f;
	float m_length2 = 128.0f;
	Player* m_player;
};
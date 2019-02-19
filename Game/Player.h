#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class PlayerBullet;
class StageKanri;
class GameCamera;
class PlayerLife;
class GameCamera;
class PlayerStatus;
class Player : public IGameObject
{
public:
	//�����o�֐�
	Player();
	~Player();
	bool Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
	void Turn();
	void AnimationController();
	void Fire();
	void Hantei();
	void Move();
	//�v���C���[�̍��W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�v���C���[�̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�v���C���[�̃��C�t���擾
	int GetLife() const
	{
		return m_life;
	}
	int GetProtLife() const
	{
		return m_protlife;
	}
	//�v���C���[���~������
	void Stop()
	{
		m_stop = true;
	}
private:
	CVector3 m_position = { 00.0f,100.0f,0.0f };
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };
	CVector3 m_movespeed_box = CVector3::Zero;
	CVector3 m_omovespeed = CVector3::Zero;
	CQuaternion m_rotation= CQuaternion::Identity;
	CQuaternion m_rotation2= CQuaternion::Identity;
	//�v���C���[�̌����ƕ��s�ȃx�N�g��
	CVector3 m_player_heikou;
	CCharacterController m_charaCon;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSpriteRender* m_heart[10];                                                                
	//�A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_Aria,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_GameOver,
		enState_WaitStartGameClear,
		enState_GameClear,
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;
	//�ړ����x��Z
	const float m_multiply = 13.0f;
	//���x����
	float m_dcs=0.97;
	float m_dush = 1.8f;
	bool m_pushB = false;
	CFont m_font;
	//�̗�
	int m_life = 1;
	int m_protlife = 1;
	float m_radian = 0;
	bool m_stop = false;
	bool m_damage = false;
	float m_damagetimer = 0;
	float m_blinktimer = 0.0f;
	PlayerBullet * m_playerbullet;
	StageKanri* m_stagekanri;
 	int m_timer = 0;
	int m_ktimer = 0;
	int m_stimer = 0;
	CPhysicsGhostObject m_ghostObject;
	GameCamera* m_gamecamera=nullptr;
	PlayerLife* m_playerlife;
	PlayerStatus* m_playerstatus;
};

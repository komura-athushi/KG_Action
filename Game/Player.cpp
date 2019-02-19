#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "PlayerBullet.h"
#include "Ugokuyuka_jouge.h"
#include "Ugokuyuka_zengo.h"
#include "Ugokuyuka_zengo2.h"
#include "Ugokuyuka_kaiten.h"
#include "Ugokuyuka_kaiten2.h"
#include "Ugokuyuka_yoko.h"
#include "Ugokuyuka_yoko2.h"
#include "Ugokuyuka_yoko3.h"
#include "Ugokuyuka_yoko4.h"
#include "Stagekanri.h"
#include "Jumpyuka.h"
#include "Jumpyuka2.h"
#include "GameCamera.h"
#include "Sword.h"
#include "SphereRing.h"
#include "PlayerLife.h"
#include "EnemyBullet.h"
#include "Meteo.h"
#include "Pyramid.h"
#include "PlayerStatus.h"
#include "Game.h"
Player::Player()
{

}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	if (m_stagekanri->GetStageNumber() == 3) {
		DeleteGO(m_playerlife);
	}
	else {
		for (m_life; m_life > 0; m_life--) {
			DeleteGO(m_heart[m_life-1]);
		}
	}
}

bool Player::Start()
{
	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"animData/unityChan/Clear.tka");
	m_animClip[enAnimationClip_Aria].Load(L"animData/unityChan/Aria.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animClip[enAnimationClip_Aria].SetLoopFlag(false);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_stagekanri = FindGO<StageKanri>("StageKanri");
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	if (m_stagekanri->GetStageNumber() == 3) {
		m_playerlife = NewGO<PlayerLife>(0, "PlayerLife");
	}
	CVector3 Pos = { -580.0f,250.0f,0.0f };
	CVector2 scale = { 200.0f,200.0f, };
	m_playerstatus = FindGO<PlayerStatus>("PlayerStatus");
	if (m_stagekanri->GetStageNumber() != 3) {
		m_protlife = m_playerstatus->GetHeart();
		m_life = m_protlife;
		for (int i = 0; i < m_playerstatus->GetHeart(); i++) {
			m_heart[i] = NewGO<prefab::CSpriteRender>(0);
			m_heart[i]->Init(L"sprite/Heart.dds", scale.x, scale.y);
			m_heart[i]->SetPosition(Pos);
			Pos.x += 110.0f;
		}
	}
	else {
		m_protlife = m_playerstatus->GetLife();
		m_life = m_protlife;
		m_position = { 900.0f,1300.0f,0.0f };
	}
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		30.0f,			//�����B
		m_position		//�����ʒu�B
	);
	m_skinModelRender->SetPosition(m_position);
	m_gamecamera = FindGO<GameCamera>("GameCamera");
	return true;
}

//�����\���̊֐�
void Player::PostRender(CRenderContext& renderContext) {

#ifndef TK_MASTER 
	m_font.Begin(renderContext);
	wchar_t aaa[100];
	swprintf(aaa,L"%f %f %f",m_position.x,m_position.y,m_position.z);
	//swprintf(aaa, L"%d", m_life);
    m_font.Draw(aaa, { 0,0 });
	m_font.End(renderContext);
#endif
}

void Player::Update()
{
	if (m_damage) {
		m_damagetimer += GameTime().GetFrameDeltaTime();
		m_blinktimer += GameTime().GetFrameDeltaTime();
		if (m_blinktimer >= 0.05f) {
			//0.2�b�o��
			bool isActive = m_skinModelRender->IsActive();
			m_skinModelRender->SetActiveFlag(!isActive);
			m_blinktimer = 0.0f;
		}
		if (m_damagetimer >= 1.0f) {
			//2�b�o�߂����̂Ń_���[�W�\���I���B
			m_skinModelRender->SetActiveFlag(true);
			m_damage = false;
		}
	}
	
	//�ړ��֌W
	if (m_stop) {
		m_movespeed.x = 0.0f;
		m_movespeed.z = 0.0f;
	}
	else {
		Move();
	}
	//�d��
	m_movespeed.y -= 800.0f * GameTime().GetFrameDeltaTime();
	//�L�����N�^�[�̌����֌W
	Turn();
	//�L�����N�^�[�̃A�j���[�V�����̏���
	if (Pad(0).IsPress(enButtonRB1)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_Aria,0.2f);
	}
	else {
		AnimationController();
	}
	//�e�I�u�W�F�N�g�Ƃ̓����蔻��
	Hantei();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	CVector3 Pos = m_omovespeed + m_movespeed;
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), Pos);
		if (m_charaCon.IsOnGround()) {
			//�n�ʂɂ����B
			m_movespeed.y = 0.0f;
		}
	//�W�����v�̃A�j���[�V���������s���ケ���ɋL��
	if (m_state == enState_Jump) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump, 0.2f);
		if (!m_charaCon.IsJump()) {
			if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				//���͂��Ȃ��Ȃ����B
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
	}
	//UnityChan������y���W��艺�ɍs���ƍŏ������蒼��
	if (m_life > 1) {
		if (m_position.y < -1500.0f) {
			m_position = CVector3::Zero;
			m_position.y = 50.0f;
			m_position.z = 000.0f;
			m_life--;
			DeleteGO(m_heart[m_life]);
		}
	}
	else if(m_life == 1){
		if (m_position.y < -1500.0f) {
			m_life--;
			DeleteGO(m_heart[m_life]);
		}
	}
	if (Pad(0).IsPress(enButtonRB1)) {
		//m_position.y = 1200.0f;
		//m_movespeed.y = 0.0f;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
	//�e����
	Fire();
	//�e���˂̃N�[���^�C��
	m_timer++;
}

void Player::Move()
{
	//���X�e�B�b�N
	CVector3 stickL;
	stickL.x = -Pad(0).GetLStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickL.y = Pad(0).GetLStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickL.z = 0.0f;
	//�ړ�
	//���X�e�B�b�N
	//L2�Ń_�b�V���@x,z�̂ݏ�Z �W�����v���Ŗ������̂݃_�b�V���\
	if (Pad(0).IsPress(enButtonLB2) && m_state != enState_Jump) {
		//�X�e�B�b�N�̍��E���͂̏���
		m_movespeed.z += +sin(m_radian)*stickL.x * m_multiply*m_dush;
		m_movespeed.x += -cos(m_radian)*stickL.x * m_multiply*m_dush;
		//�X�e�B�b�N�̏㉺���͂̏���
		m_movespeed.z += cos(m_radian)*stickL.y * m_multiply*m_dush;
		m_movespeed.x += sin(m_radian)*stickL.y * m_multiply*m_dush;
	}
	else {
		//�_�b�V�������̏���
		//�X�e�B�b�N�̍��E���͂̏���
		m_movespeed.z += +sin(m_radian)*stickL.x * m_multiply;
		m_movespeed.x += -cos(m_radian)*stickL.x * m_multiply;
		//�X�e�B�b�N�̏㉺���͂̏���
		m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
		m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
	}
	//���x����
	m_movespeed.x *= m_dcs;
	m_movespeed.z *= m_dcs;
	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_movespeed.y = 500.0f;	//������ɑ��x��ݒ肵�āA
		m_state = enState_Jump;
	}
	//�X�e�[�W2�̂݃W�����v���̔���
	else {
		if (m_stagekanri->GetStageNumber() == 2) {
			QueryGOs<Jumpyuka>("Jumpyuka", [&](Jumpyuka* jumpyuka) {
				CPhysicsGhostObject* ghostObj = jumpyuka->GetGhostObject();
				//CPhysicsGhostObject* ghostObj;
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true) {
						m_movespeed.y = 800.0f;	//������ɑ��x��ݒ肵�āA
						m_state = enState_Jump;
					}
				});
				return true;
			});
			QueryGOs<Jumpyuka2>("Jumpyuka2", [&](Jumpyuka2* jumpyuka2) {
				CPhysicsGhostObject* ghostObj = jumpyuka2->GetGhostObject();
				//CPhysicsGhostObject* ghostObj;
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true) {
						m_movespeed.y = 1000.0f;	//������ɑ��x��ݒ肵�āA
						m_state = enState_Jump;
					}
				});
				return true;
			});
		}
	}
}

void Player::Turn()
{
	CVector3 rotation = CVector3::Zero;
	//���@�̊p�x�̍���
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//�E�X�e�B�b�N
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.y = Pad(0).GetRStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.z = 0.0f;
	//����
	//�E�X�e�B�b�N
	sdegree = -stickR.x * 2.0f;
	//��]����
	m_degree += sdegree;
	m_rotation2.SetRotationDeg(CVector3::AxisY, m_degree);
	//m_movespeed����L�����N�^�[����]������
	auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ += m_player_heikou;
	moveSpeedXZ.y = 0;
	/*if (moveSpeedXZ.LengthSq() < 1.0f) {
		return;
	}*/
	m_rotation.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_player_heikou = { 0.0f,0.0f,1.0f };
	m_rotation.Multiply(m_player_heikou);
	//�L�����N�^�[��]�̏���
	if (Pad(0).IsPress(enButtonRB2)) {
		m_pushB = true;
	}
	else if (!Pad(0).IsPress(enButtonRB2) && m_pushB == true) {
		m_rotation = m_rotation2;
		m_pushB = false;
	}
	if (Pad(0).IsPress(enButtonRB2)) {
		//B�{�^���������ꂽ��J�����̒����_�ɃL�����N�^�[����]������
		m_skinModelRender->SetRotation(m_rotation2);
		m_player_heikou = { 0.0f,0.0f,1.0f };
		CQuaternion bRot = m_rotation2;
		bRot.Multiply(m_player_heikou);
	}
	else {
		m_skinModelRender->SetRotation(m_rotation);
	}
}

void Player::AnimationController()
{
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 500.0f * 500.0f) {
			//���胂�[�V�����B
			m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2f);
		}
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//�������[�V�����B
			m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2f);
		}
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			m_state = enState_Run;
		}
		else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
			m_state = enState_Idle;
		}
		break;
	case enState_GameClear:
		m_skinModelRender->PlayAnimation(enAnimationClip_Clear);
		break;
	case enState_GameOver:
		m_skinModelRender->PlayAnimation(enAnimationClip_KneelDown);
		break;
		//�W�����v�����͑��̂Ƃ��ł��
	case enState_Jump:
		break;
	}

}

void Player::Fire()
{
	if (m_gamecamera != nullptr) {
		//�v���C���[�Ɠ��������ɒe�𔭎˂�����
		if (Pad(0).IsPress(enButtonRB2) && m_timer >= 12) {
			m_playerbullet = NewGO<PlayerBullet>(0, "PlayerBullet");
			m_playerbullet->SetPosition(m_position);
			/*m_playerbullet->m_position.y += 80.0f;
			m_playerbullet->m_movespeed = m_player_heikou * 100.0f;
			m_playerbullet->m_movespeed.y = 0.0f;*/
			CVector3 Pos;
			Pos= m_gamecamera->GetTarget() - m_position;
			Pos.Normalize();
			Pos *= 80.0f;
			m_playerbullet->SetMovespeed(Pos); 
			m_timer = 0;
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Hassya.wav");
			ss->Play(false);
		}
	}
}

void Player::Hantei()
{
	m_omovespeed = CVector3::Zero;
	switch (m_stagekanri->GetStageNumber()) {
	/*�X�e�[�W1�̏���*/
	case 1:
		QueryGOs<Ugokuyuka_zengo>("Ugokuyuka_zengo", [&](Ugokuyuka_zengo* zengo) {
			CPhysicsGhostObject* ghostObj = zengo->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = zengo->GetPosition() - zengo->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_zengo2>("Ugokuyuka_zengo2", [&](Ugokuyuka_zengo2* zengo2) {
			CPhysicsGhostObject* ghostObj = zengo2->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = zengo2->GetPosition() - zengo2->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_kaiten>("Ugokuyuka_kaiten", [&](Ugokuyuka_kaiten* kaiten) {
			CPhysicsGhostObject* ghostObj = kaiten->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = kaiten->GetPosition() - kaiten->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_kaiten2>("Ugokuyuka_kaiten2", [&](Ugokuyuka_kaiten2* kaiten2) {
			CPhysicsGhostObject* ghostObj = kaiten2->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = kaiten2->GetPosition() - kaiten2->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_yoko>("Ugokuyuka_yoko", [&](Ugokuyuka_yoko* yoko) {
			CPhysicsGhostObject* ghostObj = yoko->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = yoko->GetPosition() - yoko->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_yoko2>("Ugokuyuka_yoko2", [&](Ugokuyuka_yoko2* yoko2) {
			CPhysicsGhostObject* ghostObj = yoko2->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = yoko2->GetPosition() - yoko2->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<Ugokuyuka_yoko3>("Ugokuyuka_yoko3", [&](Ugokuyuka_yoko3* yoko3) {
			CPhysicsGhostObject* ghostObj = yoko3->GetGhostObject();
			//CPhysicsGhostObject* ghostObj;
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = yoko3->GetPosition() - yoko3->GetLastFramPosition();
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_omovespeed += boxMoveSpeed;
				}
			});
			return true;
		});

		/*QueryGOs<Ugokuyuka_yoko4>("Ugokuyuka_yoko4", [&](Ugokuyuka_yoko4* yoko4) {
			CPhysicsGhostObject* ghostObj = &yoko4->m_ghostObject;
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = yoko4->m_position - yoko4->m_lastframposition;
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_pmovespeed += boxMoveSpeed;
				}
			});
			return true;
		});*/

		/*QueryGOs<Ugokuyuka_jouge>("Ugokuyuka_jouge", [&](Ugokuyuka_jouge* jouge) {
			CPhysicsGhostObject* ghostObj = &jouge->m_ghostObject;
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = jouge->m_position - jouge->m_lastframposition;
					//�{�b�N�X�̈ړ����x�����߂�
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_movespeed.y = boxMoveSpeed.y;
				}
			});
			return true;
		});*/
		break;
		/*�����܂ŃX�e�[�W1�̏���*/
		case 2:
		/*��������X�e�[�W2�̏���*/
			/*QueryGOs<Killer1>("Killer1", [&](Killer1* killer1) {
				CPhysicsGhostObject* ghostObj = &killer1->m_ghostObject;
				//CPhysicsGhostObject* ghostObj;
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true && m_ktimer>=20) {
						m_life--;
						m_ktimer = 0;
						m_omovespeed.z += cos(m_radian)* -8000;
						m_omovespeed.x += sin(m_radian)*-8000;
						m_movespeed = CVector3::Zero;
					}
				});
				return true;
			});
			QueryGOs<Killer2>("Killer2", [&](Killer2* killer2) {
				CPhysicsGhostObject* ghostObj = &killer2->m_ghostObject;
				//CPhysicsGhostObject* ghostObj;
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true && m_ktimer >= 20) {
						m_life--;
						m_ktimer = 0;
						m_omovespeed.z += cos(m_radian)* -8000;
						m_omovespeed.x += sin(m_radian)*-8000;
						m_movespeed = CVector3::Zero;
					}
				});
				return true;
			});*/
			QueryGOs<Sword>("Sword", [&](Sword* sword) {
				CPhysicsGhostObject* ghostObj = sword->GetGhostObject();
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true && m_ktimer >= 60) {
						m_life--;
						DeleteGO(m_heart[m_life]);
						m_ktimer = 0;
					}
				});
				return true;
			});
			m_ktimer++;
		break;
		/*�����܂ŃX�e�[�W2�̏���*/
		case 3:
		/*��������X�e�[�W3�̏���*/
			int Life = m_life;
		QueryGOs<Sword>("Sword", [&](Sword* sword) {
			CPhysicsGhostObject* ghostObj = sword->GetGhostObject();
			//CPhysicsGhostObject* ghostObj;
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true && m_stimer >= 15) {
					m_life--;
					m_stimer = 0;
				}
			});
			return true;
		});
		QueryGOs<SphereRing>("SphereRing", [&](SphereRing* spherering) {
			CPhysicsGhostObject* ghostObj = spherering->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true && m_stimer >= 15) {
					m_life--;
					m_stimer = 0;
				}
			});
			return true;
		});
		QueryGOs<EnemyBullet>("EnemyBullet", [&](EnemyBullet* enemybullet)
		{
			CVector3 diffs = enemybullet->GetPosition() - m_position;
			if (diffs.Length() < 90.0f && m_stimer>=15) {
				m_life--;
				m_stimer = 0;
			}
			return true;
		});
		QueryGOs<Meteo>("Meteo", [&](Meteo* meteo) {
			CPhysicsGhostObject* ghostObj = meteo->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true && m_stimer >= 15) {
					m_life--;
					m_stimer = 0;
				}
			});
			return true;
		});
		QueryGOs<Pyramid>("Pyramid", [&](Pyramid* pyramid)
		{
			CVector3 diffs = pyramid->GetPosition() - m_position;
			if (diffs.Length() < 180.0f && m_stimer>=15) {
				m_life--;
				m_stimer = 0;
			}
			return true;
		});
		if (Life != m_life) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Hidame_.wav");
			ss->Play(false);
			m_damagetimer = 0;
			m_damage = true;
		}
		m_stimer++;
		break;
		/*�����܂ŃX�e�[�W3�̏���*/
	}
}//20DOA5tauo17runiti91Ql


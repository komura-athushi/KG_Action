#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
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
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,			//半径。 
		30.0f,			//高さ。
		m_position		//初期位置。
	);
	m_skinModelRender->SetPosition(m_position);
	m_gamecamera = FindGO<GameCamera>("GameCamera");
	return true;
}

//文字表示の関数
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
			//0.2秒経過
			bool isActive = m_skinModelRender->IsActive();
			m_skinModelRender->SetActiveFlag(!isActive);
			m_blinktimer = 0.0f;
		}
		if (m_damagetimer >= 1.0f) {
			//2秒経過したのでダメージ表現終わり。
			m_skinModelRender->SetActiveFlag(true);
			m_damage = false;
		}
	}
	
	//移動関係
	if (m_stop) {
		m_movespeed.x = 0.0f;
		m_movespeed.z = 0.0f;
	}
	else {
		Move();
	}
	//重力
	m_movespeed.y -= 800.0f * GameTime().GetFrameDeltaTime();
	//キャラクターの向き関係
	Turn();
	//キャラクターのアニメーションの処理
	if (Pad(0).IsPress(enButtonRB1)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_Aria,0.2f);
	}
	else {
		AnimationController();
	}
	//各オブジェクトとの当たり判定
	Hantei();
	//キャラクターコントローラーを使用して、座標を更新。
	CVector3 Pos = m_omovespeed + m_movespeed;
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), Pos);
		if (m_charaCon.IsOnGround()) {
			//地面についた。
			m_movespeed.y = 0.0f;
		}
	//ジャンプのアニメーションだけ都合上ここに記載
	if (m_state == enState_Jump) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump, 0.2f);
		if (!m_charaCon.IsJump()) {
			if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				//入力がなくなった。
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
	}
	//UnityChanが一定のy座標より下に行くと最初からやり直し
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
	//弾発射
	Fire();
	//弾発射のクールタイム
	m_timer++;
}

void Player::Move()
{
	//左スティック
	CVector3 stickL;
	stickL.x = -Pad(0).GetLStickXF();	//アナログスティックのxの入力量を取得。
	stickL.y = Pad(0).GetLStickYF();	//アナログスティックのxの入力量を取得。
	stickL.z = 0.0f;
	//移動
	//左スティック
	//L2でダッシュ　x,zのみ乗算 ジャンプ中で無い時のみダッシュ可能
	if (Pad(0).IsPress(enButtonLB2) && m_state != enState_Jump) {
		//スティックの左右入力の処理
		m_movespeed.z += +sin(m_radian)*stickL.x * m_multiply*m_dush;
		m_movespeed.x += -cos(m_radian)*stickL.x * m_multiply*m_dush;
		//スティックの上下入力の処理
		m_movespeed.z += cos(m_radian)*stickL.y * m_multiply*m_dush;
		m_movespeed.x += sin(m_radian)*stickL.y * m_multiply*m_dush;
	}
	else {
		//ダッシュ無しの処理
		//スティックの左右入力の処理
		m_movespeed.z += +sin(m_radian)*stickL.x * m_multiply;
		m_movespeed.x += -cos(m_radian)*stickL.x * m_multiply;
		//スティックの上下入力の処理
		m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
		m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
	}
	//速度減衰
	m_movespeed.x *= m_dcs;
	m_movespeed.z *= m_dcs;
	if (Pad(0).IsTrigger(enButtonA) //Aボタンが押されたら
		&& m_charaCon.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_movespeed.y = 500.0f;	//上方向に速度を設定して、
		m_state = enState_Jump;
	}
	//ステージ2のみジャンプ床の判定
	else {
		if (m_stagekanri->GetStageNumber() == 2) {
			QueryGOs<Jumpyuka>("Jumpyuka", [&](Jumpyuka* jumpyuka) {
				CPhysicsGhostObject* ghostObj = jumpyuka->GetGhostObject();
				//CPhysicsGhostObject* ghostObj;
				PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
					if (ghostObj->IsSelf(contactObject) == true) {
						m_movespeed.y = 800.0f;	//上方向に速度を設定して、
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
						m_movespeed.y = 1000.0f;	//上方向に速度を設定して、
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
	//自機の角度の差分
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//右スティック
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
	stickR.y = Pad(0).GetRStickYF();	//アナログスティックのxの入力量を取得。
	stickR.z = 0.0f;
	//向き
	//右スティック
	sdegree = -stickR.x * 2.0f;
	//回転処理
	m_degree += sdegree;
	m_rotation2.SetRotationDeg(CVector3::AxisY, m_degree);
	//m_movespeedからキャラクターを回転させる
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
	//キャラクター回転の処理
	if (Pad(0).IsPress(enButtonRB2)) {
		m_pushB = true;
	}
	else if (!Pad(0).IsPress(enButtonRB2) && m_pushB == true) {
		m_rotation = m_rotation2;
		m_pushB = false;
	}
	if (Pad(0).IsPress(enButtonRB2)) {
		//Bボタンが押されたらカメラの注視点にキャラクターを回転させる
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
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 500.0f * 500.0f) {
			//走りモーション。
			m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2f);
		}
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//歩きモーション。
			m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機モーション
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
		//ジャンプだけは他のとこでやる
	case enState_Jump:
		break;
	}

}

void Player::Fire()
{
	if (m_gamecamera != nullptr) {
		//プレイヤーと同じ向きに弾を発射させる
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
	/*ステージ1の処理*/
	case 1:
		QueryGOs<Ugokuyuka_zengo>("Ugokuyuka_zengo", [&](Ugokuyuka_zengo* zengo) {
			CPhysicsGhostObject* ghostObj = zengo->GetGhostObject();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = zengo->GetPosition() - zengo->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = zengo2->GetPosition() - zengo2->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = kaiten->GetPosition() - kaiten->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = kaiten2->GetPosition() - kaiten2->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = yoko->GetPosition() - yoko->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = yoko2->GetPosition() - yoko2->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = yoko3->GetPosition() - yoko3->GetLastFramPosition();
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = yoko4->m_position - yoko4->m_lastframposition;
					//ボックスの移動速度を求める
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
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = jouge->m_position - jouge->m_lastframposition;
					//ボックスの移動速度を求める
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_movespeed.y = boxMoveSpeed.y;
				}
			});
			return true;
		});*/
		break;
		/*ここまでステージ1の処理*/
		case 2:
		/*ここからステージ2の処理*/
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
		/*ここまでステージ2の処理*/
		case 3:
		/*ここからステージ3の処理*/
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
		/*ここまでステージ3の処理*/
	}
}//20DOA5tauo17runiti91Ql


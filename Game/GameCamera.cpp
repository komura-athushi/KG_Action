#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("Player");
	//カメラのニアクリップとファークリップを設定する。
	//ニアクリップとファークリップの間がカメラの映す範囲になる
	MainCamera().SetNear(1.0f);     //ニアクリップ　カメラから近いほうの面
	MainCamera().SetFar(45000.0f);  //ファークリップ　カメラから遠いほうの面
	return true;
}
void GameCamera::Update()
{
	m_playerposition = m_player->GetPosition();
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
	stickR.y = Pad(0).GetRStickYF();	//アナログスティックのxの入力量を取得。
	stickR.z = 0.0f;
	//右スティックの入力
	//右スティック
	m_sdegreexz = -stickR.x * 2.0f;
	m_sdegreey = -stickR.y*2.0f;

	//回転度加算
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//上下方向のカメラ移動を制限
	if (m_degreey >= 70.0f) {
		m_degreey = 70.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//角度をラジアン単位に直す
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//視点
	MainCamera().SetTarget(m_target);
	//座標
	MainCamera().SetPosition(m_position);
	//カメラの更新。
	MainCamera().Update();
}
// 普通視点の処理 カメラの座標を移動させる、カメラの注視点をリセット
void GameCamera::Hutu()
{
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += 140.0f;
	m_target += m_player->GetPosition();
	//注視点を計算する。
	//target.y += 200.0f;
	//Y軸周りに回転させる。
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	m_toPos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(m_toPos);
	//上下の回転。
	//まずは回す軸を計算する。
	CVector3 rotAxis;
	rotAxis.Cross(m_toPos, CVector3::AxisY);
	//ベクトルを正規化する。
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(m_toPos);
	m_toPos *= m_r;
	m_position = m_target + m_toPos * 2.0f;

	/*ps = toPos / r;
	CVector3 rotAxis3;
	rotAxis3.Cross(toPos, CVector3::AxisY);
	rotAxis3.Normalize();
	rotAxis3.y -= rotAxis3.y;
	ps = rotAxis3;*/

	m_toPos *= 4;
	//m_toPos.y = 0.0f;
	m_target -= m_toPos;
	m_toPos *= 1.5f;
	/*toPos.x = -r * cos(radianx);
	toPos.y = r * sin(radiany);
	toPos.z=r*(sin(radianx)+cos(radiany));*/
	//toPos.z = r * sin(radianx);
}
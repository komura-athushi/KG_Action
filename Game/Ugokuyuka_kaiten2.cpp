#include "stdafx.h"
#include "Ugokuyuka_kaiten2.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
Ugokuyuka_kaiten2::Ugokuyuka_kaiten2()
{
}


Ugokuyuka_kaiten2::~Ugokuyuka_kaiten2()
{
	DeleteGO(m_skinModelRender);
}

bool Ugokuyuka_kaiten2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ugokuyuka_kaiten2.cmo");
	m_tyusin *= 0.03f;
	double radian = M_PI / 180 * m_degree;
	m_position.x = m_tyusin.x + m_r * cos(radian);
	m_position.z = m_tyusin.z + m_r * sin(radian);
	m_position.y = m_tyusin.y;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, { 450.0f,100.0f,520.0f });
	m_ghostObject.CreateBox(
		m_position,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 445.0f, 101.0f, 515.0f }	//第三引数はボックスのサイズ。
	);
	m_sdegree = 1.0f + 0.7*m_number;
	m_sdegree /= 0.03;
	return true;
}
void Ugokuyuka_kaiten2::Update()
{
	m_lastframposition = m_position;
	m_degree += m_sdegree * GameTime().GetFrameDeltaTime();
	double radian = M_PI / 180 * m_degree;
	m_position.x = m_tyusin.x + m_r * cos(radian);
	m_position.z = m_tyusin.z + m_r * sin(radian);
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.SetPosition(m_position);
	m_ghostObject.SetPosition(m_position);
}

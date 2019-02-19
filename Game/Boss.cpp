#include "stdafx.h" 
#include "Boss.h"
#include "Player.h"
#include "EnemyBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Sword.h"
#include "Circle.h"
#include "Circle2.h"
#include "Pyramid.h"
#include "SphereRing.h"
#include "Meteo.h"
#include "Pyramid.h"
#include "SphereRing_Big.h"
#include "BossLife.h"
#include "Star.h"
#include "PlayerBullet.h"
#include "Game.h"
Boss::Boss()
{
}
Boss::~Boss()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_sword);
	DeleteGO(m_bosslife);
	QueryGOs<EnemyBullet>("EnemyBullet", [&](EnemyBullet* enemybullet)
	{
		DeleteGO(enemybullet);
		return true;
	});
	QueryGOs<Circle>("Circle", [&](Circle* circle)
	{
		DeleteGO(circle);
		return true;
	});
	QueryGOs<Circle2>("Circle2", [&](Circle2* circle2)
	{
		DeleteGO(circle2);
		return true;
	});
	QueryGOs<Pyramid>("Pyramid", [&](Pyramid* pyramid)
	{
		DeleteGO(pyramid);
		return true;
	});
	QueryGOs<SphereRing>("SphereRing", [&](SphereRing* spherering)
	{
		DeleteGO(spherering);
		return true;
	});
	QueryGOs<Meteo>("Meteo", [&](Meteo* meteo)
	{
		DeleteGO(meteo);
		return true;
	});
	QueryGOs<SphereRing_Big>("SphereRing_Big", [&](SphereRing_Big* spherering_big)
	{
		DeleteGO(spherering_big);
		return true;
	});
}

bool Boss::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Boss.cmo");
	m_position.y = 200.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_player = FindGO<Player>("Player");
	m_phyStaticObject.CreateBoxObject(m_position, CQuaternion::Identity, {700.0f,4000.0f,700.0f});
	m_sword = NewGO<Sword>(0, "Sword");
	m_bosslife = NewGO<BossLife>(0, "BossLife");
	return true;
}
void Boss::Update()
{
	switch (m_state) {
	case 1:
		Occurs_Pyramid();
		break;
	case 2:
		Occurs_Meteo();
		break;
	case 3:
		Occurs_SphereRing();
		break;
	}
	Occurs_BulletMawari();
	Hantei();
	if (m_life <= 0) {
		m_star = NewGO<Star>(0, "Star");
		CVector3 pos = m_position;
		pos.y = 100.0f;
		m_star->SetPosition(pos);
		prefab::CSoundSource* ss;
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Bakuhatsu.wav");
		ss->Play(false);
		Game* m_game = FindGO<Game>("Game");
		m_game->BossGekiha();
		DeleteGO(this);
	}
}

void Boss::Occurs_BulletMawari()
{
	if (m_timer == 500) {
		if (rand() % 2 == 0) {
			m_bulletsdegree = 2.8f;
		}
		else {
			m_bulletsdegree = -2.8f;
		}
	}
	if (m_timer >= 500) {
		if (m_timer2 == 6) {
			float radian=m_bulletdegree*M_PI/180.0f;
			m_enemybullet = NewGO<EnemyBullet>(0, "EnemyBullet");
			CVector3 pos = m_position;
			pos.y = 50.0f;
			m_enemybullet->SetPosition(pos);
			CVector3 Pos = CVector3::Zero;
			CVector3 move = { cos(radian)*13.0f ,0.0f, sin(radian)*13.0f };
			m_enemybullet->SetMovespeed(move);
			m_enemybullet->SetDeletetime(120);
			m_timer2 = 0;
			m_bulletcount++;
		}
		m_bulletdegree += m_bulletsdegree;
		m_timer2++;
		if (m_bulletcount == 50) {
			m_timer = 0;
			m_timer2 = 0;
			m_bulletcount = 0;
			m_bulletdegree = 0;
			State();
		}
	}
	m_timer++;
}

void Boss::Occurs_Pyramid()
{
	if (m_circletimer == 300) {
		m_circle = NewGO<Circle>(0, "Circle");
		m_circletimer = 0;
		State();
	}
	m_circletimer++;
}

void Boss::Occurs_SphereRing()
{
	if (m_sphereringtimer ==200) {
		m_spherering_big = NewGO<SphereRing_Big>(0, "SphereRing_Big");
		CVector3 pos = m_position;
		pos.y = 500.0f;
		m_spherering_big->SetPosition(pos);
	}
	else if (m_sphereringtimer == 300) {
		m_sphereringtimer = 0;
		State();
	}
	m_sphereringtimer++;
}

void Boss::Occurs_Meteo()
{
	if (m_circletimer2 == 300) {
		for (int i = 0; i < 15; i++) {
			m_circle2 = NewGO<Circle2>(0, "Circle2");
			CVector3 Pos;
			Pos.y = 1.0f;
			//x,yÀ•W‚Í-930`-350,350`930‚ÌŠÔ‚É—ˆ‚é‚æ‚¤‚É‚·‚é
			if (rand() % 101 > 50) {
				Pos.z = 350.0f + rand() % 809 * 0.65f;
			}
			else {
				Pos.z = -350.0f - rand() % 809 * 0.65f;
			}

			if (rand() % 211 > 105) {
				Pos.x = 350.0f + rand() % 313 * 1.80f;
			}
			else {
				Pos.x = -350.0f - rand() % 313 * 1.80f;
			}
			if (rand() % 4 == 0) {
				if (rand() % 9 > 4) {
					Pos.x = 0.0f;
				}
				else {
					Pos.z = 0.0f;
				}
			}
			m_circle2->SetPosition(Pos);
		}
		m_circletimer2 = 0;
		State();
	}
	m_circletimer2++;
}

void Boss::Hantei()
{
	QueryGOs<PlayerBullet>("PlayerBullet", [&](PlayerBullet* playerbullet)
	{
		CVector3 Pos = m_position;
		Pos.y += 190.0f;
		CVector3 diffs = playerbullet->GetPosition() - Pos;
		if (diffs.Length() < 200.0f) {
			m_life -= 1;
			DeleteGO(playerbullet);
		}
		return true;
	});
}
void Boss::State()
{
	m_state = rand() % 3+1;
}
#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class EnemyBullet;
class Sword;
class Circle;
class Pyramid;
class SphereRing;
class Meteo;
class Circle2;
class SphereRing_Big;
class BossLife;
class Star;
class Boss : public IGameObject
{
public:
	//メンバ関数。
	Boss();
	~Boss();
	bool Start();
	void Update();
	//Occurs...発生する
	void Occurs_BulletMawari();
	void Occurs_Pyramid();
	void Occurs_SphereRing();
	void Occurs_Meteo();
	void Hantei();
	void State();
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//ボスの最初のHPを取得
	int GetProtlife() const
	{
		return m_protlife;
	}
	//ボスのHPを取得
	int GetLife() const
	{
		return m_life;
	}
private:
	//メンバ変数。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CEffect* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero;			//座標。	
	CVector3 m_scale = { 15.0f,15.0f,15.0f };
	CPhysicsStaticObject m_phyStaticObject;	//!<静的物理オブジェクト。
	int m_protlife = 200;
	int m_life = m_protlife;
	int m_timer = 0;
	int m_timer2 = 0;
	int m_circletimer = 0;
	int m_circletimer2 = 0;
	int m_sphereringtimer = 0;
	int m_sphereringtimer2 = 0;
	int m_bulletcount = 0;
	int m_sphereringcount = 0;
	float m_bulletdegree = 0.0f;
	float m_bulletsdegree = 0.0f;
	CFont m_font;
	int m_state=0;
	Player* m_player;
	EnemyBullet* m_enemybullet;
	Sword* m_sword;
	Circle* m_circle;
	Circle2* m_circle2;
	Pyramid* m_pyramid;
	SphereRing* m_spherering;
	Meteo* m_meteo;
	SphereRing_Big* m_spherering_big;
	BossLife* m_bosslife;
	Star* m_star;
};
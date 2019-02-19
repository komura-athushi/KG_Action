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
	//�����o�֐��B
	Boss();
	~Boss();
	bool Start();
	void Update();
	//Occurs...��������
	void Occurs_BulletMawari();
	void Occurs_Pyramid();
	void Occurs_SphereRing();
	void Occurs_Meteo();
	void Hantei();
	void State();
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�{�X�̍ŏ���HP���擾
	int GetProtlife() const
	{
		return m_protlife;
	}
	//�{�X��HP���擾
	int GetLife() const
	{
		return m_life;
	}
private:
	//�����o�ϐ��B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CEffect* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero;			//���W�B	
	CVector3 m_scale = { 15.0f,15.0f,15.0f };
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
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
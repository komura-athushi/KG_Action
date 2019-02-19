#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class Boss;
class Meteo;
class Circle2 : public IGameObject
{
public:
	//�����o�֐��B
	Circle2();
	~Circle2();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
private:
	//�����o�ϐ��B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CVector3 m_movespeed = CVector3::Zero; //�ړ����x�B 												
	prefab::CEffect* m_effect = nullptr;
	int m_timer = 0;
	CVector3 m_scale = {0.6,0.6,0.6};
	Player* m_player;
	Boss* m_boss;
	Meteo* m_meteo;
};
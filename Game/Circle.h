#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class Boss;
class Pyramid;
class Circle : public IGameObject
{
public:
	//�����o�֐��B
	Circle();
	~Circle();
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
	CVector3 m_scale = CVector3::One;
	Player* m_player;
	Boss* m_boss;
	Pyramid* m_pyramid;
};
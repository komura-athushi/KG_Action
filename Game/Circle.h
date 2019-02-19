#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class Boss;
class Pyramid;
class Circle : public IGameObject
{
public:
	//メンバ関数。
	Circle();
	~Circle();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
private:
	//メンバ変数。
	CVector3 m_position = CVector3::Zero;			//座標。
	CVector3 m_movespeed = CVector3::Zero; //移動速度。 												
	prefab::CEffect* m_effect = nullptr;
	int m_timer = 0;
	CVector3 m_scale = CVector3::One;
	Player* m_player;
	Boss* m_boss;
	Pyramid* m_pyramid;
};
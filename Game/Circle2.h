#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class Boss;
class Meteo;
class Circle2 : public IGameObject
{
public:
	//メンバ関数。
	Circle2();
	~Circle2();
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
	CVector3 m_scale = {0.6,0.6,0.6};
	Player* m_player;
	Boss* m_boss;
	Meteo* m_meteo;
};
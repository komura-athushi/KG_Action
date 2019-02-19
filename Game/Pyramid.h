#pragma once
class Pyramid : public IGameObject
{
public:
	//メンバ関数。
	Pyramid();
	~Pyramid();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//移動速度を設定
	void SetMovespeed(const CVector3& speed)
	{
		m_movespeed = speed;
	}
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	//メンバ変数。
	CVector3 m_position = CVector3::Zero;			//座標。
	CVector3 m_movespeed = CVector3::Zero; //移動速度。										
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;						//タイマー。
	CVector3 m_scale = { 8.0f,8.0f,8.0f };
	int m_deletetime;
};
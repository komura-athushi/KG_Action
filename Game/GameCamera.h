#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//カメラの座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//カメラの注視点を取得
	CVector3 GetTarget() const
 	{
		return m_target;
	}
	//カメラのy軸の角度を取得
	float GetDegree() const 
	{
		return m_degreexz;
	}
private:
	//カメラの座標および注視点の計算
	void Hutu();
	CVector3 m_toPos = { 0.0f, 0.0f, 0.0f };
	//円の中心座標(プレイヤーの座標)
	CVector3 m_playerposition;
	//角度
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	//回転速度
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//半径
	const float m_r = 170.0f;
	//角度をラジアン単位(π)に直したやつ
	double m_radianx;
	double m_radiany;
	//注視点
	CVector3 m_target;
	//カメラの座標
	CVector3 m_position;
	Player * m_player;	//プレイヤー。
};

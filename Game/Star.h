#pragma once
class Player;
class StageKanri;
class Star : public IGameObject
{
public:
	//メンバ関数。
	Star();
	~Star();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	//メンバ変数。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;			//座標。		
	float m_jumpspeed, m_jumStartPosY;
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	float m_kaiten = 0.0f;
	bool m_isGet = false;
	Player * m_player;
	StageKanri* m_stagekanri;
};
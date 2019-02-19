#pragma once
class Player;
class StageKanri;
class Star : public IGameObject
{
public:
	//�����o�֐��B
	Star();
	~Star();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	//�����o�ϐ��B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;			//���W�B		
	float m_jumpspeed, m_jumStartPosY;
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	float m_kaiten = 0.0f;
	bool m_isGet = false;
	Player * m_player;
	StageKanri* m_stagekanri;
};
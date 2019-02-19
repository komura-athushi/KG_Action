#pragma once
class Haikei : public IGameObject
{
public:
	//�����o�֐��B
	Haikei();
	~Haikei();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,000.0f,0.0f };			//���W�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
};
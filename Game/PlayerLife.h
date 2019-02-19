#pragma once
class Player;
class PlayerLife : public IGameObject {
public:
	PlayerLife();
	~PlayerLife();
	//IGameObjectのStart関数をオーバーライドする。  
	bool Start();
	//IGameObjectのUpdate関数をオーバーライドする。  
	void Update();
private:
	//スプライトレンダラー。  
	prefab::CSpriteRender* m_spriteRender = nullptr;  
	prefab::CSpriteRender* m_spriteRender2 = nullptr;
	//ライフ表示の初期位置
	CVector3 m_protposition = { -400,-300,0 };
	//ライフ表示の座標
	CVector3 m_position = m_protposition;
	//ライフ表示の初期の横の長さ
	float m_side = 384.0f;
	//ライフ表示の初期の縦の長さ
	float m_length = 64.0f;
	//ライフの後ろのやつの長さ
	float m_side2 = 512.0f;
	float m_length2 = 128.0f;
	Player* m_player;
};
#pragma once
//プレイヤーのステータスを管理する
class PlayerStatus : public IGameObject
{

public:
	PlayerStatus();
	~PlayerStatus();
	//IGameObjectのStart関数をオーバーライドする。  
	bool Start();
	//IGameObjectのUpdate関数をオーバーライドする。  
	void Update();
	//ステージ1,2のプレイヤーのライフを設定
	void SetHeart(const int& heart)
	{
		m_playerheart = heart;
	}
	//ステージ3のプレイヤーのライフを取得
	void SetLife(const int& life)
	{
		m_playerlife = life;
	}
	//ステージ1,2のプレイヤーのライフを取得
	int GetHeart() const
	{
		return m_playerheart;
	}
	//ステージ3のプレイヤーのライフを取得
	int GetLife() const
	{
		return m_playerlife;
	}
private:
	int m_playerheart = 5;
	int m_playerlife = 10;
};
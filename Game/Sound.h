#pragma once
//ステージ選択やステージ選択の内容をGame.cppに反映させるクラス
class Sound : public IGameObject
{
public:
	Sound();
	~Sound();
	void State();
	//IGameObjectのStart関数をオーバーライドする。  
	bool Start();
	//IGameObjectのUpdate関数をオーバーライドする。  
	void Update();
	//再生予定のBGMをセット
	void SetBGM(const int& state)
	{
		m_state2 = state;
	}
private:
	prefab::CSoundSource* m_bgmSoundSource;
	//現在再生している曲
	int m_state1 = 0;
	//再生予定の曲
	int m_state2 = 0;
};
#pragma once
//ステージ選択やステージ選択の内容をGame.cppに反映させるクラス
class StageKanri : public IGameObject 
{
public:
	StageKanri();
	~StageKanri();
	//IGameObjectのStart関数をオーバーライドする。  
	bool Start();
	//IGameObjectのUpdate関数をオーバーライドする。  
	void Update();
	//ステージを設定
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
	//ステージナンバーを取得
	int GetStageNumber() const
	{
		return m_stagenumber;
	}
	//ステージのクリア情報を取得
	bool GetClear(const int& number) const
	{
		return Clear[number];
	}
	//ステージ数を取得
	int GetStage() const
	{
		return m_stage;
	}
	//ステージクリア!
	void StageClear()
	{
		Clear[m_stagenumber-1] = true;
	}
private:
	//Stage選択
	static const int m_stage = 3;
	int m_stagenumber =1;
	bool Clear[m_stage] = { false,false,false};
};

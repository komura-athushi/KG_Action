#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class GameCamera;
class Background;
class Fade;
class Player;
class Ugokuyuka_yoko;
class Ugokuyuka_yoko2;
class Ugokuyuka_yoko3;
class Ugokuyuka_yoko4;
class Ugokuyuka_jouge;
class Ugokuyuka_zengo;
class Ugokuyuka_zengo2;
class Ugokuyuka_kaiten;
class Ugokuyuka_kaiten2;
class Goal;
class Star;
class StageKanri;
class Haikei;
class Boss;
class Jumpyuka;
class Jumpyuka2;
class Sword;
class Sound;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Stage1();
	void Stage2();
	void Stage3();
	//ゲームオーバー!!
	void Gameover() 
	{
		m_gameover = true;
	}
	//ゲームクリアー!!
	void Gameclear()
	{
		m_gameclear = true;
	}
	//ボス撃破!!
	void BossGekiha()
	{
		m_bossgekiha = true;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	prefab::CSpriteRender* m_spriteRender = nullptr;
	bool m_gameclear = false;
	bool m_gameover = false;
	bool m_scenetrans = false;
	int m_timer = 0;
	int m_kaiten1 = 0;
	int m_kaiten2 = 0;
	int m_yoko3 = 0;
	int m_sword = 0;
	bool m_bossgekiha = false;
	Player* m_player = nullptr;
	Background* m_background = nullptr;
	GameCamera* m_gamecamera;
	Goal* m_goal = nullptr;
	Star* m_star = nullptr;
	StageKanri* m_stagekanri;
	Haikei* m_haikei;
	Boss* m_boss;
	Jumpyuka* m_jumpyuka;
	Jumpyuka2* m_jumpyuka2;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	Fade * m_fade = nullptr;
	std::vector<prefab::CDirectionLight*> m_directionLigList;	//ディレクションライト。
	prefab::CDirectionLight* lig;
	CLevel m_level;							//レベル。
	//各オブジェクトの可変長配列
	std::vector<Ugokuyuka_yoko*> m_yokoList;		
	std::vector<Ugokuyuka_yoko2*> m_yoko2List;
	std::vector<Ugokuyuka_yoko3*> m_yoko3List;
	std::vector<Ugokuyuka_yoko4*> m_yoko4List;
	std::vector<Ugokuyuka_zengo*> m_zengoList;
	std::vector<Ugokuyuka_zengo2*> m_zengo2List;
	std::vector<Ugokuyuka_kaiten*> m_kaitenList;
	std::vector<Ugokuyuka_kaiten2*> m_kaiten2List;
	std::vector<Jumpyuka*> m_jumpList;
	std::vector<Jumpyuka2*> m_jump2List;
	std::vector<Sword*> m_swordList;
};


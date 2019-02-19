#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"
#include "Background.h"
#include "GameCamera.h"
#include "Ugokuyuka_yoko.h"
#include "Ugokuyuka_yoko2.h"
#include "Ugokuyuka_yoko3.h"
#include "Ugokuyuka_yoko4.h"
#include "Ugokuyuka_jouge.h"
#include "Ugokuyuka_zengo.h"
#include "Ugokuyuka_zengo2.h"
#include "Ugokuyuka_kaiten.h"
#include "Ugokuyuka_kaiten2.h"
#include "Goal.h"
#include "Star.h"
#include "StageSelect.h"
#include "Stagekanri.h"
#include "Haikei.h"
#include "Boss.h"
#include "GameOver.h"
#include "Jumpyuka.h"
#include "Jumpyuka2.h"
#include "Sword.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Sound.h"
Game::Game()
{
	
}

Game::~Game()
{
	switch (m_stagekanri->GetStageNumber()) {
	case 1:
		DeleteGO(m_gamecamera);
		DeleteGO(m_background);
		if (m_gameclear) {
			DeleteGO(m_spriteRender);
		}
		else {
			DeleteGO(m_star);
		}
		DeleteGO(m_goal);
		DeleteGO(m_haikei);
		for (auto& yoko : m_yokoList) {
			DeleteGO(yoko);
		}
		for (auto& yoko2 : m_yoko2List) {
			DeleteGO(yoko2);
		}
		for (auto& yoko3 : m_yoko3List) {
			DeleteGO(yoko3);
		}
		for (auto& yoko4 : m_yoko4List) {
			DeleteGO(yoko4);
		}
		for (auto& zengo : m_zengoList) {
			DeleteGO(zengo);
		}
		for (auto& zengo2 : m_zengo2List) {
			DeleteGO(zengo2);
		}
		for (auto& kaiten : m_kaitenList) {
			DeleteGO(kaiten);
		}
		for (auto& kaiten2 : m_kaiten2List) {
			DeleteGO(kaiten2);
		}
		DeleteGO(m_player);
		break;
	case 2:
		DeleteGO(m_player);
		DeleteGO(m_gamecamera);
		DeleteGO(m_background);
		if (m_gameclear) {
			DeleteGO(m_spriteRender);
		}
		else {
			DeleteGO(m_star);
		}
		DeleteGO(m_haikei);
		for (auto& jump : m_jumpList) {
			DeleteGO(jump);
		}
		for (auto& jump2 : m_jump2List) {
			DeleteGO(jump2);
		}
		for (auto& sword : m_swordList) {
			DeleteGO(sword);
		}
		break;
	case 3:
		DeleteGO(m_player);
		DeleteGO(m_gamecamera);
		DeleteGO(m_background);
		if (m_gameclear) {
			DeleteGO(m_spriteRender);
		}
		else if(m_gameover && !m_bossgekiha){
			DeleteGO(m_boss);
		}
		else if (m_gameover && m_bossgekiha) {
			m_star = FindGO<Star>("Star");
			DeleteGO(m_star);
		}
		break;
	}
}

bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();
	
	lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetDirection({ 0.707f, -0.707f, 0.0f });
	lig->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	m_directionLigList.push_back(lig);

	lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetDirection({ 0.707f, 0.707f, 0.0f });
	lig->SetColor({ 5.0f, 5.0f, 5.0f, 1.0f });
	m_directionLigList.push_back(lig);

	lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetDirection({ -0.707f, -0.707f, 0.0f });
	lig->SetColor({ 5.0f, 5.0f, 5.0f, 1.0f });
	m_directionLigList.push_back(lig);

	lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetDirection({ 0.0f, 1.0f, 0.0f });
	lig->SetColor({ 5.0f, 5.0f, 5.0f, 1.0f });
	m_directionLigList.push_back(lig);
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.707f, -0.707f, 0.0f });
	m_stagekanri = FindGO<StageKanri>("StageKanri");
	Sound* m_sound = FindGO<Sound>("Sound");
	switch (m_stagekanri->GetStageNumber()) {
		case 1:
		Stage1();
		m_haikei = NewGO<Haikei>(0, "Haikei");
		m_sound->SetBGM(1);
			break;
		case 2:
			Stage2();
			m_haikei = NewGO<Haikei>(0, "Haikei");
			m_sound->SetBGM(2);
		break;
		case 3:
			Stage3();
			m_sound->SetBGM(3);
			break;
	}
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_gameclear) {
				NewGO<StageSelect>(0, "StageSelect");
				DeleteGO(this);
			}
			else if(m_gameover){
				NewGO<GameOver>(0, "GameOver");
				DeleteGO(this);
			}
		}
	}
	else {
		if (m_timer==100) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		else if (m_player->GetLife()<=0) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			m_gameover = true;
		}
		else if (Pad(0).IsTrigger(enButtonSelect) && !m_gameclear) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			m_gameover = true;
		}
	}

	if (m_gameclear && m_scenetrans == false) {
		m_spriteRender = NewGO<prefab::CSpriteRender>(0);
		m_spriteRender->Init(L"sprite/GameClear.dds", 1280.0f, 720.0f);
		m_scenetrans = true;
	}
	else if (m_scenetrans) {
		m_timer++;
	}
}

void Game::Stage1()
{
	//レベルを構築する。
	m_level.Init(L"level/level01.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"Ugokuyuka_yoko") == true) {
			//Starオブジェクト。
			Ugokuyuka_yoko* yoko = NewGO<Ugokuyuka_yoko>(0,"Ugokuyuka_yoko");
			yoko->SetPosition(objData.position);
			yoko->SetProtPosition(objData.position);
			//yoko->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_yokoList.push_back(yoko);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Ugokuyuka_yoko2") == true) {
			//Starオブジェクト。
			Ugokuyuka_yoko2* yoko2 = NewGO<Ugokuyuka_yoko2>(0, "Ugokuyuka_yoko2");
			yoko2->SetPosition(objData.position);
			yoko2->SetProtPosition(objData.position);
			//yoko2->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_yoko2List.push_back(yoko2);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Ugokuyuka_yoko3") == true) {
			//Starオブジェクト。
			Ugokuyuka_yoko3* yoko3 = NewGO<Ugokuyuka_yoko3>(0,"Ugokuyuka_yoko3");
			yoko3->SetPosition(objData.position);
			yoko3->SetNumber(m_yoko3);
			m_yoko3++;
			//yoko3->m_protposition = objData.position;
			//yoko3->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_yoko3List.push_back(yoko3);
			//フックしたのでtrueを返す。
			return true;
		}
		/*else if (objData.EqualObjectName(L"Ugokuyuka_yoko4") == true) {
			//Starオブジェクト。
			Ugokuyuka_yoko4* yoko4 = NewGO<Ugokuyuka_yoko4>(0, "Ugokuyuka_yoko4");
			yoko4->m_position = objData.position;
			//yoko4->m_protposition = objData.position;
			//yoko4->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_yoko4List.push_back(yoko4);
			//フックしたのでtrueを返す。
			return true;
		}*/
		else if (objData.EqualObjectName(L"Ugokuyuka_zengo") == true) {
			//Starオブジェクト。
			Ugokuyuka_zengo* zengo = NewGO<Ugokuyuka_zengo>(0, "Ugokuyuka_zengo");
			zengo->SetPosition(objData.position);
			zengo->SetProtPosition(objData.position);
			//zengo->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_zengoList.push_back(zengo);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Ugokuyuka_zengo2") == true) {
			//Starオブジェクト。
			Ugokuyuka_zengo2* zengo2 = NewGO<Ugokuyuka_zengo2>(0, "Ugokuyuka_zengo2");
			zengo2->SetPosition(objData.position);
			zengo2->SetProtPosition(objData.position);
			//zengo2->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_zengo2List.push_back(zengo2);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Ugokuyuka_kaiten") == true) {
			//Starオブジェクト。
			Ugokuyuka_kaiten* kaiten = NewGO<Ugokuyuka_kaiten>(0, "Ugokuyuka_kaiten");
			kaiten->SetPosition(objData.position);
			kaiten->SetNumber(m_kaiten1);
			m_kaiten1++;
			//kaiten->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_kaitenList.push_back(kaiten);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Ugokuyuka_kaiten2") == true) {
			//Starオブジェクト。
			Ugokuyuka_kaiten2* kaiten2 = NewGO<Ugokuyuka_kaiten2>(0, "Ugokuyuka_kaiten2");
			kaiten2->SetPosition(objData.position);
			kaiten2->SetNumber(m_kaiten2);
			m_kaiten2++;
			//kaiten2->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_kaiten2List.push_back(kaiten2);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Background1") == true) {
			m_background = NewGO<Background>(0, "Background");
			//m_background->m_position = objData.position;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Goal") == true) {
			m_goal = NewGO<Goal>(0, "Goal");
			m_goal->SetPosition(objData.position);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unityちゃん。
			//プレイヤーのインスタンスを生成する。
			m_player = NewGO<Player>(0, "Player");
			//m_player->m_position = objData.position;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"star") == true) {
			m_star = NewGO<Star>(0, "Star");
			m_star->SetPosition(objData.position);
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
}  

void Game::Stage2()
{
	//レベルを構築する。
	m_level.Init(L"level/level02.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"Jumpyuka") == true) {
			//Starオブジェクト。
			Jumpyuka* jump = NewGO<Jumpyuka>(0, "Jumpyuka");
			jump->SetPosition(objData.position);
			//後で削除するのでリストに積んで記憶しておく。
			m_jumpList.push_back(jump);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Jumpyuka2") == true) {
			//Starオブジェクト。
			Jumpyuka2* jump2 = NewGO<Jumpyuka2>(0, "Jumpyuka2");
			jump2->SetPosition(objData.position);
			//yoko2->m_scale = objData.scale;
			//後で削除するのでリストに積んで記憶しておく。
			m_jump2List.push_back(jump2);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"Background2") == true) {
			m_background = NewGO<Background>(0, "Background");
			//m_background->m_position = objData.position;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unityちゃん。
			//プレイヤーのインスタンスを生成する。
			m_player = NewGO<Player>(0, "Player");
			m_player->SetPosition(objData.position);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"DoubleSword") == true) {
			//プレイヤーのインスタンスを生成する。
			Sword* sword = NewGO<Sword>(0, "Sword");
			sword->SetPosition(objData.position);
			sword->SetSdegree(2.0f + m_sword*0.7f);
			m_swordList.push_back(sword);
			m_sword++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"star") == true) {
			m_star = NewGO<Star>(0, "Star");
			m_star->SetPosition(objData.position);
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
}

void Game::Stage3()
{
	m_player = NewGO<Player>(0, "Player");
	m_background = NewGO<Background>(0, "Background");
	m_boss = NewGO<Boss>(0, "Boss");
}
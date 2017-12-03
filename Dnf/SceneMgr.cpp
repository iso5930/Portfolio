#include "StdAfx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MyMenu.h"
#include "MyEdit.h"
#include "SeriaRoom.h"
#include "Elvengard.h"
#include "Villmark.h"
#include "VillmarkStage2.h"
#include "BossRoom.h"

CSceneMgr* CSceneMgr::m_pInstance = NULL;

CSceneMgr::CSceneMgr(void)
	:m_pScene(NULL), m_eType(SCENE_END), m_bChangeScene(false)
{

}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::Init(void)
{

}

int CSceneMgr::Progress(void)
{
	if(m_bChangeScene)
	{
		m_bChangeScene = false;
		SetScene(m_eType);
	}

	if(m_pScene)
		m_pScene->Progress();
	
	return 0;
}

void CSceneMgr::Render(HDC _hdc)
{
	if(m_pScene)
		m_pScene->Render(_hdc);
}

void CSceneMgr::Release(void)
{
	if(m_pScene)
	{
		SAFE_DELETE(m_pScene);
	}
}

void CSceneMgr::SetScene(SCENE_STATE eState)
{
	if(m_pScene)
	{
		SAFE_DELETE(m_pScene);
	}

	switch(eState)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
	
		break;

	case SCENE_MENU:
		m_pScene = new CMyMenu;
		break;

	case SCENE_EDIT:
		m_pScene = new CMyEdit;
		m_pScene->SetSceneState(SCENE_EDIT);
		break;

	case SCENE_SERIAROOM:
		m_pScene = new CSeriaRoom;
		m_pScene->SetSceneState(SCENE_SERIAROOM);
		break;

	case SCENE_ELVENGARD:
		m_pScene = new CElvengard;
		m_pScene->SetSceneState(SCENE_ELVENGARD);
		break;

	case SCENE_VILLMARK:
		m_pScene = new CVillmark;
		m_pScene->SetSceneState(SCENE_VILLMARK);
		break;

	case SCENE_VILLMARK2:
		m_pScene = new CVillmarkStage2;
		m_pScene->SetSceneState(SCENE_VILLMARK2);
		break;

	case SCENE_BOSSROOM:
		m_pScene = new CBossRoom;
		m_pScene->SetSceneState(SCENE_BOSSROOM);
		break;
	}

	m_pScene->Init();
}

void CSceneMgr::ChangeScene(SCENE_STATE eState)
{
	m_bChangeScene = true;
	m_eType = eState;
}
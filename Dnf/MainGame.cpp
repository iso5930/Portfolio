#include "StdAfx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Obj.h"
#include "Factory.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "ImageMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "RenderMgr.h"
#include "ImageMgr.h"
#include "SoundMgr.h"


CMainGame::CMainGame(void)
{
	srand(unsigned(time(NULL)));

	//콘솔
	
	//AllocConsole(); 
	//freopen( "CONOUT$",  "wt", stdout);
	//SetConsoleTitleA("Debug");
	CSoundMgr::GetInstance()->LoadSoundFile();
	
}

CMainGame::~CMainGame(void)
{
	//콘솔
	//FreeConsole();
	Release();
}

void CMainGame::Init(void)
{
	m_hdc = GetDC(g_hwnd);

	list<CObj*>* pObjList = CObjMgr::GetInstance()->GetList();

	CSceneMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->SetScene(SCENE_LOGO);
	CImageMgr::GetInstance()->Init();
	CCollisionMgr::GetInstance()->Init();
	CCollisionMgr::GetInstance()->SetMonsterList(&(pObjList[OBJ_MONSTER]));
		
	//fps
	m_dwTime = GetTickCount();
	lstrcpy(m_szFps, L"");
	m_iFps = 0;
}

int CMainGame::Progress(void)
{
	CMouse::SetMousePos();
	CKeyMgr::GetInstance()->SetKeyState();
	CSceneMgr::GetInstance()->Progress();

	return 0;
}

void CMainGame::Render(void)
{
	CSceneMgr::GetInstance()->Render(m_hdc);

	//fps
	if(m_dwTime + 1000 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		wsprintf(m_szFps, L"FPS : %d", m_iFps);

		SetWindowText(g_hwnd, m_szFps);

		m_iFps = 0;
	}
	++m_iFps;

}

void CMainGame::Release(void)
{
	CKeyMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CImageMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CRenderMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
}	
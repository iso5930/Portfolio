#include "StdAfx.h"
#include "Logo.h"
#include "Define.h"
#include "SceneMgr.h"


CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Init(void)
{
	m_hVideo = MCIWndCreate(g_hwnd, NULL,
			MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD
			,L"../Video/Logo.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);
	m_dwTime = GetTickCount();
}

int CLogo::Progress(void)
{
	if(m_dwTime + 4000 < GetTickCount())
	{
		CSceneMgr::GetInstance()->ChangeScene(SCENE_MENU);
	}
	if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::GetInstance()->ChangeScene(SCENE_MENU);
	}
	return 0;
}

void CLogo::Render(HDC _hdc)
{
	
}

void CLogo::Release(void)
{
	MCIWndClose(m_hVideo);
}
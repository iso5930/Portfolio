#include "StdAfx.h"
#include "MyMenu.h"
#include "ImageMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
CMyMenu::CMyMenu(void)
	:m_ImageSize(0,0,800,600)
{

}

CMyMenu::~CMyMenu(void)
{
	Release();
}

void CMyMenu::Init(void)
{
	m_BackBuffer.LoadBmp(L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadImage("BackBuffer", L"../Image/BackBuffer.bmp");
	CImageMgr::GetInstance()->LoadBmp("Menu", L"../Image/Main.bmp");
	CImageMgr::GetInstance()->LoadImage("Start", L"../Image/Button/start.bmp");
	CImageMgr::GetInstance()->LoadImage("Edit", L"../Image/Button/Edit.bmp");
	CImageMgr::GetInstance()->LoadImage("Exit", L"../Image/Button/Exit.bmp");
	CImageMgr::GetInstance()->LoadBmp("Cutin", L"../Image/Cutin.bmp");

	m_ButtonList.push_back( new CMyButton("Start",200, 500, 116, 45) );
	m_ButtonList.push_back( new CMyButton("Edit", 400, 500, 116, 45) );
	m_ButtonList.push_back( new CMyButton("Exit", 600, 500, 116, 45) );

	CSoundMgr::GetInstance()->PlayBGM(L"character_stage_ds.ogg");
}

int CMyMenu::Progress(void)
{
	list<CMyButton*>::iterator iter = m_ButtonList.begin();
	list<CMyButton*>::iterator iter_end = m_ButtonList.end();

	for(iter; iter != iter_end; ++iter)
	{
		int iResult = (*iter)->Progress();

		if (iResult == 1)
		{
			CSceneMgr::GetInstance()->ChangeScene(SCENE_SERIAROOM);
		}
		else if (iResult == 2)
		{
			CSceneMgr::GetInstance()->ChangeScene(SCENE_EDIT);
		}
	}
	return 0;
}

void CMyMenu::Render(HDC _hdc)
{
	list<CMyButton*>::iterator iter = m_ButtonList.begin();
	list<CMyButton*>::iterator iter_end = m_ButtonList.end();

	CImageMgr::GetInstance()->ImageRender(m_BackBuffer.GetMemDC(), "Menu", m_ImageSize,0,0,123,123,123);	
	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->Render(m_BackBuffer.GetMemDC());
	}

	
	
	BitBlt(_hdc,0,0,800,600,m_BackBuffer.GetMemDC(),0,0,SRCCOPY);
}

void CMyMenu::Release(void)
{
	list<CMyButton*>::iterator iter = m_ButtonList.begin();
	list<CMyButton*>::iterator iter_end = m_ButtonList.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_ButtonList.clear();
}	